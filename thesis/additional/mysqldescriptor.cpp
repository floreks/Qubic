QString MySQLDescriptor::getColumnType(const QString &tableName, const QString &columnName) {
    QSqlDatabase db = QcDatabase::getInstance()->getDatabase("info");
    QSqlQuery query(QString("SELECT data_type FROM " + getTypeSchema() + ".columns WHERE table_schema ='%1' AND table_name='%2' AND column_name='%3'").arg(
                        QcDatabase::getInstance()->getDatabase().databaseName(),tableName,columnName), db);

...

    return query.value(0).toString();
}