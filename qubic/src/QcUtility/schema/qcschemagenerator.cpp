#include "qcschemagenerator.h"

using std::list;

#include "database/databasedescriptor.h"
#include "database/databaseinfo.h"

QcLogger* QcSchemaGenerator::logger;

QList<QcMetaTable> QcSchemaGenerator::getTables(Properties *properties) {
    QList<QcMetaTable> result;
    DatabaseDescriptor *descriptor = DatabaseInfo::getDescriptor(QcDatabase::getInstance()->getDatabase().driverName());

    for(QString tableName : descriptor->getTables()) {
        QcMetaTable table(tableName);
        logger->debug("Mapping table: " + tableName);
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
        logger->debug("Mapping field: '" + columnType + "' to type '" + columnTypeMap + "'");
        if(id == 0) {
            logger->error("Type: '" + columnType + "' is not supported");
            continue;
        }
        QcMetaField *field = static_cast<QcMetaField*>(QMetaType::create(id));
        logger->debug("Setting column name: " + columnName);
        field->setName(columnName);
        if(descriptor->isPrimaryKey(tableName,columnName)) {
            logger->debug("Column: " + columnName + " is primary key.");
            field->setPrimaryKey(true);
        }

        if(descriptor->isForeignKey(tableName,columnName)) {
            logger->debug("Column: " + columnName + " is foreign key.");
            field->setType(descriptor->getFKTable(tableName,columnName));
            field->setForeignKey(true);
        }

        result.append(field);
    }

    return result;
}

// --------------------- ------------- --------------------- //

QcSchema QcSchemaGenerator::getSchema(Properties *properties) {
    logger = QcLogger::getInstance();
    return QcSchema(getTables(properties));
}
