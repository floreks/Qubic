#include "qcdatabase.h"

#include <QSqlError>
#include <QSqlRecord>

#include "properties/qcpropertiesvalidator.h"
#include "properties/qcproperties.h"
#include "databaseinfo.h"

QSharedPointer<QcDatabase> QcDatabase::instance;

QcDatabase *QcDatabase::getInstance(Properties *properties) {
    if (instance.isNull()) instance = QSharedPointer<QcDatabase>(new QcDatabase(properties));
    return instance.data();
}

QcDatabase *QcDatabase::getInstance() {
    if(instance.isNull()) instance = QSharedPointer<QcDatabase>(new QcDatabase());
    return instance.data();
}

void QcDatabase::setUp(Properties *properties) {
    QSqlDatabase db = QSqlDatabase::addDatabase(QString("q"+properties->getProperty("driver","name")).toUpper());
    db.setHostName(properties->getProperty("host","address"));
    db.setDatabaseName(properties->getProperty("database","name"));
    db.setPort(properties->getProperty("host","port").toInt());
    db.setUserName(properties->getProperty("username"));
    db.setPassword(properties->getProperty("password"));

    db = QSqlDatabase::addDatabase(QString("q"+properties->getProperty("driver","name")).toUpper(),"info");
    DatabaseDescriptor *descriptor = DatabaseInfo::getDescriptor(db.driverName());
    db.setHostName(properties->getProperty("host","address"));
    db.setDatabaseName(descriptor->getTypeSchema());
    db.setPort(properties->getProperty("host","port").toInt());
    db.setUserName(properties->getProperty("username"));
    db.setPassword(properties->getProperty("password"));

    delete descriptor;
}

QcDatabase::QcDatabase(Properties *properties) {
    setUp(properties);
}

QcDatabase::QcDatabase() {

    Properties *properties = new QcProperties();
    if(!QcPropertiesValidator::validate(properties)) {
        return;
    }

    setUp(properties);
}

bool QcDatabase::open() {
    QSqlDatabase db;
    QStringList list = QSqlDatabase::connectionNames();
    for(QString name : list) {
        db = QSqlDatabase::database(name);
        if(!db.open()) {
            logger->error(tr("Could not open database. Please check configuration."));
            logger->error(tr(db.lastError().text().toStdString().c_str()));
            return 0;
        }
    }

    logger->info(tr("Connection to database has been established."));
    return 1;
}


void QcDatabase::close() {
    logger->info(tr("Closing database connections."));

    QStringList list = QSqlDatabase::connectionNames();
    for(QString name : list) {
        QSqlDatabase db = QSqlDatabase::database(name);
        if(db.isOpen()) {
            db.close();
        }
    }

    for(QString name : list) {
        QSqlDatabase::removeDatabase(name);
    }
}

QSqlDatabase QcDatabase::getDatabase(const QString &connectionName)const {
    if(connectionName == "defaultConnection") {
        return QSqlDatabase::database();
    }
    return QSqlDatabase::database("info");
}
