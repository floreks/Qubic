#ifndef QCDATABASE_H
#define QCDATABASE_H

#include <QSharedPointer>
#include <QtSql/QSqlDatabase>
#include "qclogger.h"
#include "properties/properties.h"

class QcDatabase
{
    Q_DECLARE_TR_FUNCTIONS(QcDatabase)

public:
    static QcDatabase* getInstance(QString driver, Properties *properties);
private:
    QSqlDatabase db;
    QcLogger *logger = QcLogger::getInstance();
    static QSharedPointer<QcDatabase> instance;
    QcDatabase(QString driver, Properties *properties);
};

#endif // QCDATABASE_H
