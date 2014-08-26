#ifndef QBPERSISTENCEHELPER_H
#define QBPERSISTENCEHELPER_H

#include <QsLog.h>
#include <QString>
#include <QSqlDriver>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <../QbCore/qbproperties.h>
#include <../QbCore/qbpersistable.h>

class QbPersistenceHelper
{
public:
    static QSqlDatabase* getDatabase();
    static void initializeTransactions();
    static void initializeDatabase();
    static void connect();
    static void disconnect();
    static QList<QbPersistable *> *getSynchronizedObjects();

protected:
    static QList<QbPersistable*> synchronizedObjects;
    static bool transactionsEnabled;
    static QSqlDatabase db;
};

#endif // QBPERSISTENCEHELPER_H
