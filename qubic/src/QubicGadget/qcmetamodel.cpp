#include "qcmetamodel.h"
#include <QSharedData>
#include <QDebug>
#include <QMetaClassInfo>
#include <QMultiHash>
#include <QString>
#include <QStringList>
#include <QSet>
#include "qcmetafield.h"
#include "qccolumn.h"
#include "exception/qcerrorcode.h"

/**
 * @brief The QcMetaModelData class
 * @internal
 */
class QcMetaModelData : public QSharedData{
public:
    QString schemaName;
    QString tableName;
    QSet<QcMetaField*> fields;
};

/**
 * @brief The InitHelper class
 * @internal
 */
class InitHelper {
public:
    /**
     * @brief capitalize string
     * @param str to be capitalized
     * @return string with first character capitalized
     */
    //TODO move to utilities
    QString capitalize(const QString &str)  {
        QString tmp = str;
        tmp[0] = str[0].toUpper();
        return tmp;
    }

    /**
     * @brief readClassInfo extract all Q_CLASSINFO information
     * @param meta data provider filled with Q_CLASSINFO information
     * @return QMultiHash with read data, storage is a singleton value, however fields occur multiple time
     */
    QMultiHash<QString,QStringList> readClassInfo(const QMetaObject *meta){
        const int optionsIndex = meta->classInfoOffset();
        const int optionsCount = meta->classInfoCount();
        QMultiHash<QString,QStringList> options;
        QString name;
        QStringList values;
        for(int i = optionsIndex ; i < optionsCount + optionsIndex ; i++){
            name = meta->classInfo(i).name();
            values = QString(meta->classInfo(i).value()).split(",");
            options.insert(name, values);
        }
        return options;
    }

    /**
     * @brief registerFieldInfo
     * @param data
     * @param model
     * @param meta
     */
    //TODO move regexed to utilities
    //TODO attach logger
    //TODO improve metaextraction
    void registerFieldInfo(const QStringList &data,
                           QcMetaModelData *model,
                           const QMetaObject *meta){
        qDebug() << "Registering field info [" << data << "]";
        QcMetaField *metaField = new QcMetaField();
        QcColumn column;
        for(QString str : data){
            if(str.contains("name")){
                column.setName(str.split("=").takeAt(1));
            }else if(str.contains("property")){
                QString property = str.split("=").takeAt(1);
                qint16 propertyIndex = meta->indexOfProperty(property.toLatin1());

                if(propertyIndex > 0){
                    qDebug() << "Valid property " << property << " found at " << propertyIndex;
                    metaField->setMetaProperty(meta->property(propertyIndex));
                }else{
                    qDebug() << "Invalid property " << property;
                }
            }else if(str.contains("options")){
                QStringList options = str.split("=").takeAt(1).remove(QRegExp("[{}]")).split(";");
                QcColumn::ColumnOptions columnOptions(QcColumn::EMPTY_OPTIONS);
                QRegExp booleanHunter("\\b(true|false)\\b"),
                        numericValueHunter("[a-zA-Z\(\\)]");
                for(QString option : options){
                    if(option.contains("unique")){
                        if(booleanHunter.indexIn(option) > 0){
                            if(booleanHunter.cap(1) == "true"){
                                qDebug() << "Property is unique";
                                columnOptions = columnOptions & QcColumn::UNIQUE;
                            }
                        }
                    }else if(option.contains("maxLength")){
                        qint16 length = option.remove(numericValueHunter).toUInt();
                        if(length > 0){
                            qDebug() << "MaxLength = " << length;
                            column.setMaxLength(length);
                        }else{
                            qWarning() << "Could not parse column maxLength, assuming default 30";
                            column.setMaxLength(30);
                        }
                    }else if(option.contains("primaryKey")){
                        if(booleanHunter.indexIn(option) > 0){
                            if(booleanHunter.cap(1) == "true"){
                                qDebug() << "Property is primaryKey";
                                columnOptions = columnOptions & QcColumn::PRIMARY_KEY;
                            }
                        }
                    }else if(option.contains("notNull")){
                        if(booleanHunter.indexIn(option) > 0){
                            if(booleanHunter.cap(1) == "true"){
                                qDebug() << "Property can not be null";
                                columnOptions = columnOptions & QcColumn::NOT_NULL;
                            }
                        }
                    }else if(option.contains("default")){
                        QVariant defaultValue = option.split("(").takeAt(1).split(")").takeAt(0);
                        column.setDefaultValue(defaultValue);
                        qDebug() << "Property has default value = " << defaultValue;
                    }
                }
                column.setOptions(columnOptions);
            }
        }
        metaField->setColumn(column);
        model->fields.insert(metaField);
    }

    void registerStorageInfo(const QStringList &data,
                             QcMetaModelData *model){
        qDebug() << "Registering schema info [" << data << "]";
        for(QString str : data){
            if(str.contains("schema")){
                model->schemaName = str.split("=").takeAt(1);
            }else if(str.contains("table")){
                model->tableName = str.split("=").takeAt(1);
            }
        }
    }
};

QcMetaModel::QcMetaModel() :
    metaData(new QcMetaModelData){
}

QcMetaModel::QcMetaModel(const QcMetaModel &rhs) :
    metaData(rhs.metaData){
}

QcMetaModel &QcMetaModel::operator=(const QcMetaModel &rhs){
    if (this != &rhs)
        metaData.operator=(rhs.metaData);
    return *this;
}

//TODO add logger support
QcMetaModel QcMetaModel::registerInternalModel(const QMetaObject *meta){
    QcMetaModel metaModel;
    InitHelper initHelper;
    QMultiHash<QString,QStringList> classInfo = initHelper.readClassInfo(meta);
    QcErrorCode::InitErrorCodes errors(QcErrorCode::NO_ERROR);
    if (classInfo.size() == 0) {
        errors = QcErrorCode::NOT_QC_MODEL;
    }else{
        QHashIterator<QString,QStringList> it(classInfo);
        while(it.hasNext()){
            it.next();
            if(it.key() == "storage"){
                initHelper.registerStorageInfo(
                            it.value(),
                            metaModel.metaData.data()
                            );
            }else if(it.key() == "field"){
                initHelper.registerFieldInfo(
                            it.value(),
                            metaModel.metaData.data(),
                            meta);
            }
        }
    }

    switch(errors){
    case QcErrorCode::NOT_QC_MODEL:
        qWarning() << meta->className() << "is not a QcModel";
    }

    return metaModel;
}

QcMetaModel::~QcMetaModel(){
}
