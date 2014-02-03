#include "qcpropertiesmanager.h"

#include <QXmlSchema>
#include <QXmlSchemaValidator>
#include <QString>

#include "QcStaticProperties.h"

QString QcPropertiesManager::propertiesFileName;
QString QcPropertiesManager::schemaFileName;
QcLogger* QcPropertiesManager::logger = QcLogger::getInstance();
QDomDocument QcPropertiesManager::xmlDocument;

// PRIVATE METHODS //

QByteArray QcPropertiesManager::readFile(const QString &filename) {
    QFile file(filename);
    if(file.open(QFile::ReadOnly)) {
        QByteArray result = file.readAll();
        file.close();
        return result;
    }
    logger->error(file.errorString());
    return QByteArray();
}

// END OF PRIVATE METHODS //

bool QcPropertiesManager::validate(const QString &propertiesPath) {
    QXmlSchema schema;
    QXmlSchemaValidator validator;
    
    QByteArray schemaData, propertiesData;
    
    if(propertiesFileName.isEmpty() && schemaFileName.isEmpty()) {
        schemaData = readFile(propertiesPath + "\\" + QC_SCHEMA_FILE);
        propertiesData = readFile(propertiesPath  + "\\" + QC_PROPERTIES_FILE);
    } else if(!propertiesFileName.isEmpty() && !schemaFileName.isEmpty()) {
        schemaData = readFile(propertiesPath  + "\\" + schemaFileName);
        propertiesData = readFile(propertiesPath  + "\\" + propertiesFileName);
    }

    if(schemaData.isEmpty() || propertiesData.isEmpty()) {
        logger->error(tr("Could not read properties files."));
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

    xmlDocument.setContent(propertiesData);
    logger->info(tr("Properties and schema validated successfuly."));

    return 1;
}

void QcPropertiesManager::overrideProperties(const QString filename) {
    logger->info(tr("Overriding properties file."));
    propertiesFileName = filename;
}

void QcPropertiesManager::overrideSchema(const QString filename) {
    logger->info(tr("Overriding schema file."));
    schemaFileName = filename;
}

QString QcPropertiesManager::getUsername() {
    return xmlDocument.elementsByTagName("q:username").at(0).firstChild().nodeValue();
}

QString QcPropertiesManager::getPassword() {
    return xmlDocument.elementsByTagName("q:password").at(0).firstChild().nodeValue();
}

QString QcPropertiesManager::getDriverName() {
    return xmlDocument.elementsByTagName("q:driver").at(0).toElement().attributeNode("name").nodeValue();
}

QString QcPropertiesManager::getHost() {
    return xmlDocument.elementsByTagName("q:host").at(0).toElement().attributeNode("address").nodeValue();
}

short int QcPropertiesManager::getPort() {
    return xmlDocument.elementsByTagName("q:host").at(0).toElement().attributeNode("port").nodeValue().toInt();
}
