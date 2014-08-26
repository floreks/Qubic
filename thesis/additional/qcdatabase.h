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
    static QcDatabase* getInstance(Properties *properties);
    static QcDatabase* getInstance();
    bool open();
    void close();
    QSqlDatabase getDatabase(const QString &connectionName = "defaultConnection")const;
private:
    QcLogger *logger = QcLogger::getInstance();
    static QSharedPointer<QcDatabase> instance;
    QcDatabase(Properties *properties);
    QcDatabase();

    void setUp(Properties *properties);
};

#endif // QCDATABASE_H
