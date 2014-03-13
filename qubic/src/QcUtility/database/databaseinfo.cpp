#include "databaseinfo.h"

#include "mysqldescriptor.h"

DatabaseDescriptor* DatabaseInfo::getDescriptor(const QString &driverName) {

    if(driverName.contains("MYSQL",Qt::CaseInsensitive)) {
        return new MySQLDescriptor();
    }

    return NULL;
}
