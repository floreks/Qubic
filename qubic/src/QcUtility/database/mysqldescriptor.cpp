#include "mysqldescriptor.h"

#include <QSqlQuery>
#include "qcdatabase.h"

QString MySQLDescriptor::getColumnType(const QString &tableName, const QString &columnName) {
    QSqlDatabase db = QcDatabase::getInstance()->getDatabase("info");
    QSqlQuery query(QString("SELECT data_type FROM " + getTypeSchema() + ".columns WHERE table_schema ='%1' AND table_name='%2' AND column_name='%3'").arg(
                        QcDatabase::getInstance()->getDatabase().databaseName(),tableName,columnName), db);

    if(!query.exec()) {
        logger->error(tr("(getColumnType)Query failed to exec"));
        return QString();
    }

    if(!query.next()) {
        logger->error(tr("(getColumnType)Query did not give any results."));
        return QString();
    }

    return query.value(0).toString();
}

bool MySQLDescriptor::isPrimaryKey(const QString &tableName, const QString &columnName) {
    QSqlDatabase db = QcDatabase::getInstance()->getDatabase("info");
    QSqlQuery query(QString("SELECT column_key FROM " + getTypeSchema() + ".columns WHERE table_schema ='%1' AND table_name='%2' AND column_name='%3'").arg(
                        QcDatabase::getInstance()->getDatabase().databaseName(),tableName,columnName), db);

    if(!query.exec()) {
        logger->error(tr("(isPrimaryKey)Query failed to exec"));
        return 0;
    }

    if(!query.next()) {
        logger->error(tr("(isPrimaryKey)Query did not give any results."));
        return 0;
    }

    return query.value(0).toString().contains("PRI");
}

bool MySQLDescriptor::isForeignKey(const QString &tableName, const QString &columnName) {
    QSqlDatabase db = QcDatabase::getInstance()->getDatabase("info");
    QSqlQuery query(QString("SELECT column_key FROM " + getTypeSchema() + ".columns WHERE table_schema ='%1' AND table_name='%2' AND column_name='%3'").arg(
                        QcDatabase::getInstance()->getDatabase().databaseName(),tableName,columnName), db);

    if(!query.exec()) {
        logger->error(tr("(isForeignKey)Query failed to exec"));
        return 0;
    }

    if(!query.next()) {
        logger->error(tr("(isForeignKey)Query did not give any results."));
        return 0;
    }

    return query.value(0).toString().contains("MUL");
}

QString MySQLDescriptor::getFKTable(const QString &tableName, const QString &columnName) {
    QSqlDatabase db = QcDatabase::getInstance()->getDatabase("info");
    QSqlQuery query(QString("SELECT REFERENCED_TABLE_NAME FROM " + getTypeSchema() + ".KEY_COLUMN_USAGE where table_schema='%1' and table_name='%2' and column_name='%3'").arg(
                        QcDatabase::getInstance()->getDatabase().databaseName(),tableName,columnName), db);

    if(!query.exec()) {
        logger->error(tr(QString("(getFKTable)Query failed to exec("+tableName+")("+columnName+")").toStdString().c_str()));
        return QString();
    }

    if(!query.next()) {
        logger->error(tr(QString("(getFKTable)Query failed to exec("+tableName+")("+columnName+")").toStdString().c_str()));
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
    QSqlQuery query(QString("SELECT data_type FROM " + getTypeSchema() + ".columns WHERE table_schema ='%1' AND table_name='%2'").arg(
                        QcDatabase::getInstance()->getDatabase().databaseName(),tableName), db);

    if(!query.exec()) {
        logger->error(tr("(getColumnTypes)Query failed to exec"));
        return result;
    }

    while(query.next()) {
        result.append(query.value(0).toString());
    }

    return result;
}
