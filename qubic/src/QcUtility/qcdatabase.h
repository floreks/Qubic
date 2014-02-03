#ifndef QCDATABASE_H
#define QCDATABASE_H

#include <QSharedPointer>
#include <QObject>
#include "qclogger.h"

class QcDatabase
{
public:
    static QcDatabase* getInstance();
    static QcDatabase* getInstance(QString propertiesPath);
    virtual ~QcDatabase() {}
private:
    QcLogger *logger = QcLogger::getInstance();
    static QSharedPointer<QcDatabase> instance;
    QcDatabase(QString propertiesPath = (QDir::currentPath() + "\\resources"));
};

#endif // QCDATABASE_H
