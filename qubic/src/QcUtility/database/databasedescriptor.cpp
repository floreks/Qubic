#include "databasedescriptor.h"

#include <QSqlRecord>
#include <QSqlDatabase>

#include "qcdatabase.h"

DatabaseDescriptor::DatabaseDescriptor() {
    this->logger = QcLogger::getInstance();
}

QStringList DatabaseDescriptor::getTables() {
    return QcDatabase::getInstance()->getDatabase().tables();
}

QStringList DatabaseDescriptor::getColumns(const QString &tableName) {
    QStringList result;
    QSqlRecord columns = QcDatabase::getInstance()->getDatabase().record(tableName);
    for(int i=0;i<columns.count();i++) {
        result.append(columns.fieldName(i));
    }
    return result;
}
