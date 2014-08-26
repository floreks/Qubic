#include "qbdatabase.h"

QbDatabase* QbDatabase::instance = NULL;

QbDatabase::QbDatabase()
{
    QbLoggerHelper::initialize();
    QbPersistenceHelper::initializeDatabase();
    QbPersistenceHelper::initializeTransactions();
    QbPersistenceHelper::connect();
}

QbDatabase::~QbDatabase()
{
    QbPersistenceHelper::disconnect();
}

QbDatabase *QbDatabase::getInstance()
{
    if (instance == NULL) instance = new QbDatabase();
    return instance;
}

void QbDatabase::deleteInstance()
{
    delete instance;
    instance = NULL;
}

QSqlDatabase* QbDatabase::getDatabase()
{
    return QbPersistenceHelper::getDatabase();
}

QList<QbPersistable*>* QbDatabase::getSynchronizedObjects()
{
    return QbPersistenceHelper::getSynchronizedObjects();
}

bool QbDatabase::checkDriver(QString driverName)
{
    if(this->driverName == NULL) this->driverName = QbPersistenceHelper::getDatabase()->driverName();
    return (this->driverName == driverName);
}

int QbDatabase::store(QbPersistable& object)
{
    if(checkDriver("QMYSQL"))
    {
        return QbMySQLPersistenceHelper::store(object);
    }
    else
    {
        QLOG_FATAL() << "Store method for driver " + this->driverName + " is not implemented";
        return -1;
    }
}

void QbDatabase::update(QbPersistable& object)
{
    if(checkDriver("QMYSQL"))
    {
        QbMySQLPersistenceHelper::update(object);
    }
    else
    {
        QLOG_FATAL() << "Update method for driver " + this->driverName + " is not implemented";
    }
}

void QbDatabase::remove(QbPersistable& object)
{
    if(checkDriver("QMYSQL"))
    {
        QbMySQLPersistenceHelper::remove(object);
    }
    else
    {
        QLOG_FATAL() << "Remove method for driver " + this->driverName + " is not implemented";
    }
}

QList<QbPersistable*> QbDatabase::load(QbPersistable& object, int id)
{
    if(checkDriver("QMYSQL"))
    {
        return QbMySQLPersistenceHelper::load(object, id);
    }
    else
    {
        QLOG_FATAL() << "Load method for driver " + this->driverName + " is not implemented";
        return QList<QbPersistable*>();
    }
}

QList<QbPersistable*> QbDatabase::load(QbQuery *query)
{
    if(checkDriver("QMYSQL"))
    {
        return QbMySQLPersistenceHelper::load(query);
    }
    else
    {
        QLOG_FATAL() << "Load method for driver " + this->driverName + " is not implemented";
        return QList<QbPersistable*>();
    }
}
