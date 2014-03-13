#include "qcmetatable.h"

QcMetaTable::QcMetaTable(QString tableName) {
    this->tableName = tableName;
}

void QcMetaTable::addField(QcMetaField *field) {
    fields.push_back(field);
}

void QcMetaTable::setFields(QList<QcMetaField *> fields) {
    this->fields = fields;
}

bool QcMetaTable::operator <(const QcMetaTable &obj)const {
    if(obj.tableName.compare(tableName) <= 0) {
        return false;
    }

    return true;
}

QList<QcMetaField *> QcMetaTable::getFields()const {
    return fields;
}

QString QcMetaTable::getName()const {
    return tableName;
}

QDebug operator <<(QDebug os, const QcMetaTable &t) {
    os << "{ " << t.tableName << " }";
    return os;
}
