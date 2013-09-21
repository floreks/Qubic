#ifndef QCCORE_H
#define QCCORE_H

#include "qccore_global.h"
#include "qclogger.h"

class QCCORESHARED_EXPORT QcObject : public QObject
{
    Q_OBJECT
private:
    QcLogger *logger = QcLogger::getInstance();
public:
    explicit QcObject(QObject *parent = 0);
    ~QcObject();
    Q_INVOKABLE QString getName() { return this->staticMetaObject.className(); }
};

#endif // QCCORE_H
