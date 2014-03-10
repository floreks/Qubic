#include "qcschemagenerator.h"

using std::list;

QList<QcMetaTable> QcSchemaGenerator::getTables(QcDatabase *db) {
    QList<QcMetaTable> result;

    return result;
}

QList<QcMetaField> QcSchemaGenerator::getFields(QcMetaTable table) {
    QList<QcMetaField> result;

    return result;
}

// --------------------- ------------- --------------------- //

QcSchema QcSchemaGenerator::getSchema(QcDatabase *db, Properties *properties) {
    qRegisterHelper<QcMetaField>();
//    int id = QMetaType::type("QcStringField");
//    QcMetaField *field = static_cast<QcMetaField*>(QMetaType::create(id));
//    field->setName("id");

    return QcSchema();
}
