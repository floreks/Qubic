#ifndef DATABASEINFO_H
#define DATABASEINFO_H

#include <QString>

#include "databasedescriptor.h"

class DatabaseInfo
{
public:
    DatabaseInfo() = delete;
    static DatabaseDescriptor* getDescriptor(const QString &driverName);
};

#endif // DATABASEINFO_H
