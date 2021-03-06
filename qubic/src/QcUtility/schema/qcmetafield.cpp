#include "qcmetafield.h"

QcMetaField::QcMetaField() {
    primaryKey = false;
}

QcMetaField::QcMetaField(QString fieldName) {
    this->fieldName = fieldName;
    primaryKey = false;
    foreignKey = false;
}

QString QcMetaField::getName()const {
    return fieldName;
}

void QcMetaField::setName(const QString &fieldName) {
    this->fieldName = fieldName;
}

void QcMetaField::setType(const QString &typeName) {
    this->typeName = typeName;
}

bool QcMetaField::isPrimaryKey()const {
    return primaryKey;
}

void QcMetaField::setPrimaryKey(bool pk) {
    primaryKey = pk;
}

void QcMetaField::setForeignKey(bool fk) {
    this->foreignKey = fk;
}

bool QcMetaField::isForeignKey()const {
    return foreignKey;
}
