#include "qcmetafield.h"

QcMetaField::QcMetaField(QString fieldName) {
    this->fieldName = fieldName;
}

QString QcMetaField::getName()const {
    return fieldName;
}

void QcMetaField::setName(QString fieldName) {
    this->fieldName = fieldName;
}
