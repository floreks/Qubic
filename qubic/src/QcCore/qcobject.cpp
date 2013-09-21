#include "qcobject.h"

QcObject::QcObject(QObject *parent) : QObject(parent) {
    logger->debug(this, "Creating QcObject object");
}

QcObject::~QcObject() {
    logger->debug(this, "Destroying QCObject object");
}
