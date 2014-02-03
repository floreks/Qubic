#include "qcpersistable.h"

QcPersistable::QcPersistable(QObject *parent) : QcObject(parent) {
    logger->debug(this, tr("Creating QcPersistable object"));
}

QcPersistable::~QcPersistable() {
    logger->debug(this, tr("Destroying QcPersistable object"));
}
