#include "qcdatabase.h"

#include <QDir>

#include "qcpropertiesmanager.h"

QSharedPointer<QcDatabase> QcDatabase::instance;

QcDatabase *QcDatabase::getInstance() {
    if (instance.isNull()) instance = QSharedPointer<QcDatabase>(new QcDatabase());
    return instance.data();
}

QcDatabase *QcDatabase::getInstance(QString propertiesPath) {
    if (instance.isNull()) instance = QSharedPointer<QcDatabase>(new QcDatabase(propertiesPath));
    return instance.data();
}

QcDatabase::QcDatabase(QString propertiesPath) {
    QcPropertiesManager manager;
    manager.validate(propertiesPath);
    qDebug() << manager.getPort();
}
