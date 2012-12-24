#ifndef QCCONNECTIONMANAGER_H
#define QCCONNECTIONMANAGER_H

#include "qubicorm.h"
#include <QSqlDatabase>
#include <QSharedData>

QC_USES(QCConnectionManagerData)
class QC_EXPORT QCConnectionManager : public QObject {
    Q_OBJECT
public:
    QCConnectionManager(QObject *parent = 0);
    QCConnectionManager(const QCConnectionManager &,QObject *parent = 0);
    QCConnectionManager &operator=(const QCConnectionManager &);
    ~QCConnectionManager();

private:
    QSharedDataPointer<QCConnectionManagerData> data;
};

#endif // QCCONNECTIONMANAGER_H
