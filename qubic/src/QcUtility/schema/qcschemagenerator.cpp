#include "qcschemagenerator.h"

using std::list;

QList<QcMetaTable> QcSchemaGenerator::getTables() {
    QList<QcMetaTable> result;



    return result;
}

QList<QcMetaField*> QcSchemaGenerator::getFields(const QString &tableName) {
    QList<QcMetaField*> result;

    return result;
}

// --------------------- ------------- --------------------- //

QcSchema QcSchemaGenerator::getSchema(Properties *properties) {
    qRegisterHelper<QcMetaField>();

    QcSchema result;
//    int id = QMetaType::type("QcStringField");
//    QcMetaField *field = static_cast<QcMetaField*>(QMetaType::create(id));
//    field->setName("id");

//    if(db->getDatabase().isOpen()) {

//    }



    return result;
}
