#include "qcschemagenerator.h"

using std::list;

#include "database/databasedescriptor.h"
#include "database/databaseinfo.h"

QList<QcMetaTable> QcSchemaGenerator::getTables(Properties *properties) {
    QList<QcMetaTable> result;
    DatabaseDescriptor *descriptor = DatabaseInfo::getDescriptor(QcDatabase::getInstance()->getDatabase().driverName());

    for(QString tableName : descriptor->getTables()) {
        QcMetaTable table(tableName);
        table.setFields(getFields(tableName,properties));
        result.append(table);
    }

    return result;
}

QList<QcMetaField*> QcSchemaGenerator::getFields(const QString &tableName, Properties *properties) {
    qRegisterHelper<QcMetaField>();

    QList<QcMetaField*> result;
    DatabaseDescriptor *descriptor = DatabaseInfo::getDescriptor(QcDatabase::getInstance()->getDatabase().driverName());
    QMap<QString,QString> typeMapping = properties->getAttributesMap("map","fromType","toType");

    for(QString columnName : descriptor->getColumns(tableName)) {
        QString columnType = descriptor->getColumnType(tableName,columnName);
        QString columnTypeMap = typeMapping[columnType];
        int id = QMetaType::type(columnTypeMap.toStdString().c_str());
        if(id == 0) {
            return result;
        }
        QcMetaField *field = static_cast<QcMetaField*>(QMetaType::create(id));
        field->setName(columnName);
        result.append(field);
    }

    return result;
}

// --------------------- ------------- --------------------- //

QcSchema QcSchemaGenerator::getSchema(Properties *properties) {
    QcSchema result;

    getTables(properties);



    return result;
}
