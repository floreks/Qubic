#ifndef QCDATABASE_H
#define QCDATABASE_H

#include <QSharedPointer>
#include <QObject>
#include "qclogger.h"
#include "properties/QcStaticProperties.h"

class QcDatabase
{
public:
    static QcDatabase* getInstance();
    static QcDatabase* getInstance(QString propertiesPath);
    virtual ~QcDatabase() {}
private:
    QcLogger *logger = QcLogger::getInstance();
    static QSharedPointer<QcDatabase> instance;
    QcDatabase(QString propertiesPath = PROPERTIES_DIR);
};

#endif // QCDATABASE_H
