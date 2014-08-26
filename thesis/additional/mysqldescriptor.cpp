#include "mysqldescriptor.h"

#include <QSqlQuery>
#include "qcdatabase.h"

QString MySQLDescriptor::getColumnType(const QString &tableName, const QString &columnName) {
    QSqlDatabase db = QcDatabase::getInstance()->getDatabase("info");
    QSqlQuery query(QString("SELECT data_type FROM information_schema.columns WHERE table_schema ='%1' AND table_name='%2' AND column_name='%3'").arg(
                        QcDatabase::getInstance()->getDatabase().databaseName(),tableName,columnName), db);

	...
	
    return query.value(0).toString();
}

bool MySQLDescriptor::isPrimaryKey(const QString &tableName, const QString &columnName) {
    QSqlDatabase db = QcDatabase::getInstance()->getDatabase("info");
    QSqlQuery query(QString("SELECT column_key FROM information_schema.columns WHERE table_schema ='%1' AND table_name='%2' AND column_name='%3'").arg(
                        QcDatabase::getInstance()->getDatabase().databaseName(),tableName,columnName), db);

	...

    return query.value(0).toString().contains("PRI");
}

bool MySQLDescriptor::isForeignKey(const QString &tableName, const QString &columnName) {
    QSqlDatabase db = QcDatabase::getInstance()->getDatabase("info");
    QSqlQuery query(QString("SELECT column_key FROM information_schema.columns WHERE table_schema ='%1' AND table_name='%2' AND column_name='%3'").arg(
                        QcDatabase::getInstance()->getDatabase().databaseName(),tableName,columnName), db);

	...

    return query.value(0).toString().contains("MUL");
}

QString MySQLDescriptor::getFKTable(const QString &tableName, const QString &columnName) {
    QSqlDatabase db = QcDatabase::getInstance()->getDatabase("info");
    QSqlQuery query(QString("SELECT REFERENCED_TABLE_NAME FROM information_schema.KEY_COLUMN_USAGE where table_schema='%1' and table_name='%2' and column_name='%3'").arg(
                        QcDatabase::getInstance()->getDatabase().databaseName(),tableName,columnName), db);

	...

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

	...

    return result;
}
