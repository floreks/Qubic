#include "mysqldescriptor.h"

#include <QSqlQuery>
#include "qcdatabase.h"

QString MySQLDescriptor::getColumnType(const QString &tableName, const QString &columnName) {
    QSqlDatabase db = QcDatabase::getInstance()->getDatabase("info");
    QSqlQuery query(QString("SELECT data_type FROM information_schema.columns WHERE table_schema ='%1' AND table_name='%2' AND column_name='%3'").arg(
                        QcDatabase::getInstance()->getDatabase().databaseName(),tableName,columnName), db);

    if(!query.exec()) {
        logger->error(tr("Query failed to exec"));
        return QString();
    }

    if(!query.next()) {
        logger->error(tr("Query did not give any results."));
        return QString();
    }

    return query.value(0).toString();
}

QString MySQLDescriptor::getTypeSchema() {
    return "information_schema";
}

QStringList MySQLDescriptor::getColumnTypes(const QString &tableName) {
    QStringList result;
    QSqlDatabase db = QcDatabase::getInstance()->getDatabase("info");
    QSqlQuery query(QString("SELECT data_type FROM information_schema.columns WHERE table_schema ='%1' AND table_name='%2'").arg(
                        QcDatabase::getInstance()->getDatabase().databaseName(),tableName), db);

    if(!query.exec()) {
        logger->error(tr("Query failed to exec"));
        return result;
    }

    while(query.next()) {
        result.append(query.value(0).toString());
    }

    return result;
}
