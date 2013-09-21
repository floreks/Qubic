#ifndef QCPERSISTABLE_H
#define QCPERSISTABLE_H

#include "qcobject.h"

class QCCORESHARED_EXPORT QcPersistable : public QcObject
{
    Q_OBJECT
private:
    QcLogger *logger = QcLogger::getInstance();
public:
    explicit QcPersistable(QObject *parent = 0);
    ~QcPersistable();
    Q_INVOKABLE QString getName() { return this->staticMetaObject.className(); }
};

#endif // QCPERSISTABLE_H
