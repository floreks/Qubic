#include "qcintegerfield.h"

QString QcIntegerField::getType()const {
    return typeName.isEmpty() ? "qint32" : typeName;
}
