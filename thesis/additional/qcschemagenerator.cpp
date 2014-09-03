QList<QcMetaTable> QcSchemaGenerator::getTables(Properties *properties) {
    QList<QcMetaTable> result;
    DatabaseDescriptor *descriptor = DatabaseInfo::getDescriptor(QcDatabase::getInstance()->getDatabase().driverName());

    for(QString tableName : descriptor->getTables()) {
        if(QcSchemaValidator::hasErrors()) {
            return result;
        }
        QcMetaTable table(tableName);
        logger->debug("Mapping table: " + tableName);
        table.setFields(getFields(tableName,properties));
        QcSchemaValidator::checkTable(table);
        result.append(table);
    }

    setRelations(result);

    return result;
}
