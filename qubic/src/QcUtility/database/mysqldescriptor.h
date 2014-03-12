#ifndef MYSQLDESCRIPTOR_H
#define MYSQLDESCRIPTOR_H

#include "databasedescriptor.h"

class MySQLDescriptor : public DatabaseDescriptor
{
public:
    using DatabaseDescriptor::DatabaseDescriptor;
    ~MySQLDescriptor() {}

    QString getColumnType(const QString &tableName, const QString &columnName);
    QStringList getColumnTypes(const QString &tableName);
    QString getTypeSchema();
};

#endif // MYSQLDESCRIPTOR_H
