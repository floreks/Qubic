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
    bool isPrimaryKey(const QString &tableName, const QString &columnName);
    bool isForeignKey(const QString &tableName, const QString &columnName);
    QString getFKTable(const QString &tableName, const QString &columnName);
};

#endif // MYSQLDESCRIPTOR_H
