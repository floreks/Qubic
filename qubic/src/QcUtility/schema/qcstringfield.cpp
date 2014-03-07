#include "qcstringfield.h"

QcStringField::QcStringField(QString fieldName) : QcMetaField(fieldName) {
    this->fieldType = "QString";
}

QString QcStringField::getType()const {
    return fieldType;
}
