#include "qcintegerfield.h"

QcIntegerField::QcIntegerField(QString fieldName) : QcMetaField(fieldName) {
    fieldType = "qint32";
}

QString QcIntegerField::getType()const {
    return fieldType;
}
