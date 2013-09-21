#include "qcpersistable.h"

QcPersistable::QcPersistable(QObject *parent) : QcObject(parent) {
    logger->debug(this, "Creating QcPersistable object");
}

QcPersistable::~QcPersistable() {
    logger->debug(this, "Destroying QcPersistable object");
}
