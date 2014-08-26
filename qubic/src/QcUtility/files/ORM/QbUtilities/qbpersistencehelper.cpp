#include "qbpersistencehelper.h"

QList<QbPersistable*> QbPersistenceHelper::synchronizedObjects = QList<QbPersistable*>();
bool QbPersistenceHelper::transactionsEnabled = false;
QSqlDatabase QbPersistenceHelper::db;

QList<QbPersistable*>* QbPersistenceHelper::getSynchronizedObjects()
{
    return &synchronizedObjects;
}

QSqlDatabase* QbPersistenceHelper::getDatabase()
{
    return &db;
}

void QbPersistenceHelper::initializeDatabase()
{
    QString driver = QbProperties::getInstance()->getProperty("qubic.database.driver");
    QString hostname = QbProperties::getInstance()->getProperty("qubic.database.hostname");
    QString dbname = QbProperties::getInstance()->getProperty("qubic.database.dbname");
    QString username = QbProperties::getInstance()->getProperty("qubic.database.username");
    QString password = QbProperties::getInstance()->getProperty("qubic.database.password");
    db = QSqlDatabase::addDatabase(driver);
    db.setHostName(hostname);
    db.setDatabaseName(dbname);
    db.setUserName(username);
    db.setPassword(password);
    QLOG_INFO() << "Database " + hostname + ":" + dbname + " successfully initialized";
}

void QbPersistenceHelper::initializeTransactions()
{
    QString tansactionsEnabled = QbProperties::getInstance()->getProperty("qubic.transactions.enabled");
    bool areTransactionsEnabled = (tansactionsEnabled.toStdString() == "true");
    if(QSqlDatabase::database().driver()->hasFeature(QSqlDriver::Transactions) && areTransactionsEnabled)
    {
        QLOG_INFO() << "Transactions successfully enabled";
        transactionsEnabled = true;
    }
    else
    {
        if(QSqlDatabase::database().driver()->hasFeature(QSqlDriver::Transactions))
        {
            QLOG_INFO() << "Transactions disabled";
            transactionsEnabled = false;
        }
        else
        {
            QLOG_WARN() << "Transactions disabled, your database does not support them";
            transactionsEnabled = false;
        }
    }
}

void QbPersistenceHelper::connect()
{
    if(db.open()) QLOG_INFO() << "Connected to database";
    else QLOG_FATAL() << "Cannot connect to database";
}

void QbPersistenceHelper::disconnect()
{
    db.close();
}
