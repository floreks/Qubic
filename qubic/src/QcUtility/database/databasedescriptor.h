#ifndef DATABASEDESCRIPTOR_H
#define DATABASEDESCRIPTOR_H

#include <QCoreApplication>

#include "qclogger.h"

class DatabaseDescriptor
{
    Q_DECLARE_TR_FUNCTIONS(QcDatabase)

protected:
    QcLogger *logger;
public:
    explicit DatabaseDescriptor();
    virtual ~DatabaseDescriptor() {}

    QStringList getTables();
    QStringList getColumns(const QString &tableName);
    virtual QString getColumnType(const QString &tableName, const QString &columnName) = 0;
    virtual QStringList getColumnTypes(const QString &tableName) = 0;
    virtual QString getTypeSchema() = 0;
};

#endif // DATABASEDESCRIPTOR_H
