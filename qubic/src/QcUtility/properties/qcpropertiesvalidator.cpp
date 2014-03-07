#include "qcpropertiesvalidator.h"

#include <QXmlSchema>
#include <QXmlSchemaValidator>
#include <QCoreApplication>

QcLogger* QcPropertiesValidator::logger;

bool QcPropertiesValidator::validate(Properties *properties) {
    logger = QcLogger::getInstance();
    QXmlSchema schema;
    QXmlSchemaValidator validator;
    QByteArray schemaData, propertiesData;

    schemaData = properties->getSchemaData();
    propertiesData = properties->getPropertyData();

    if(schemaData.isEmpty() || propertiesData.isEmpty()) {
        logger->error(tr("Could not read properties file."));
        return 0;
    }

    if(!schema.load(schemaData)) {
        logger->error(tr("Schema data not valid."));
        return 0;
    }

    validator.setSchema(schema);
    if(!validator.validate(propertiesData)) {
        logger->error(tr("Properties data not valid."));
        return 0;
    }

    logger->info(tr("Properties and schema validated successfully."));
    return 1;
}
