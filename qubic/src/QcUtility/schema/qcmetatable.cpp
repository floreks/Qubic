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
    os << "{ " << t.tableName << " }\n";
    for(int i=0;i<t.getFields().size();i++) {
        os << "{ " << t.getFields().at(i)->getName() << ", " << t.getFields().at(i)->getType() << " } ";
    }
    os << "\n";
    return os;
}

void QcMetaTable::setJointTable(QcMetaTable *table) {
    this->jointTable = table;
}

void QcMetaTable::setRelatedTable(QcMetaTable *table) {
    this->relatedTable = table;
}

void QcMetaTable::setRelationType(RelationType type) {
    this->relationType = type;
}

QcMetaTable* QcMetaTable::getJointTable()const {
    return jointTable;
}

QcMetaTable* QcMetaTable::getRelatedTable()const {
    return relatedTable;
}

RelationType QcMetaTable::getRelationType()const {
    return relationType;
}
