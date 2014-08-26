#ifndef QBDATABASE_H
#define QBDATABASE_H

#include <QSqlDatabase>
#include <qbpersistable.h>
#include <qbproperties.h>
#include <qbquery.h>
#include <../QbUtilities/qbloggerhelper.h>
#include <../QbUtilities/qbpersistencehelper.h>
#include <../QbUtilities/qbmysqlpersistencehelper.h>
#include <../QsLog/QsLog.h>

class QbDatabase
{
public:
    static QbDatabase* getInstance();
    static void deleteInstance();
    int store(QbPersistable& object);
    void update(QbPersistable &object);
    void remove(QbPersistable& object);
    QList<QbPersistable*> load(QbPersistable& object, int id = -1);
    QList<QbPersistable*> load(QbQuery* query);
    QSqlDatabase* getDatabase();
    QList<QbPersistable*> *getSynchronizedObjects();
    bool checkDriver(QString driverName);

private:
    QbDatabase();
    ~QbDatabase();
    static QbDatabase* instance;
    QString driverName = NULL;

};

#endif // QBDATABASE_H
