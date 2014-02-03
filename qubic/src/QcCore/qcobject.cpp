#include "qcobject.h"

QcObject::QcObject(QObject *parent) : QObject(parent) {
    logger->debug(this, tr("Creating QcObject object"));
}

QcObject::~QcObject() {
    logger->debug(this, tr("Destroying QcObject object"));
}
