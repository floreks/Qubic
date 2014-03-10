#include "qcdatabase.h"

#include <QSqlError>

QSharedPointer<QcDatabase> QcDatabase::instance;

QcDatabase *QcDatabase::getInstance(QString driver, Properties *properties) {
    if (instance.isNull()) instance = QSharedPointer<QcDatabase>(new QcDatabase(driver,properties));
    return instance.data();
}

QcDatabase::QcDatabase(QString driver, Properties *properties) {

    db = QSqlDatabase::addDatabase(driver);
    db.setHostName(properties->getProperty("host","address"));
    db.setDatabaseName(properties->getProperty("database","name"));
    db.setPort(properties->getProperty("host","port").toInt());
    db.setUserName(properties->getProperty("username"));
    db.setPassword(properties->getProperty("password"));
}

bool QcDatabase::open() {
    if(!db.open()) {
        logger->error(tr("Could not open database. Please check configuration."));
        logger->error(tr(db.lastError().text().toStdString().c_str()));
        return 0;
    }

    logger->info(tr("Connection to database has been established."));
    return 1;
}


void QcDatabase::close() {
    logger->info(tr("Closing database connection."));
    db.close();
    instance.clear();
}
