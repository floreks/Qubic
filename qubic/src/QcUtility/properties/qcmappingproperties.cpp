#include "qcmappingproperties.h"

#include <qcstaticproperties.h>

QcMappingProperties::QcMappingProperties() {
    logger = QcLogger::getInstance();
    propertiesFileName = QC_MAPPING_FILE;
    schemaFileName = QC_MAPPING_SCHEMA_FILE;
}

QByteArray QcMappingProperties::getPropertyData() {
    QByteArray file = readFile(QC_PROPERTIES_DIR + "\\" + propertiesFileName);
    xmlDocument.setContent(file);
    return file;
}

QByteArray QcMappingProperties::getSchemaData() {
    return readFile(QC_PROPERTIES_DIR + "\\" + schemaFileName);
}

QString QcMappingProperties::getProperty(QString tag) {
    return xmlDocument.elementsByTagName("qc:"+tag).at(0).firstChild().nodeValue();
}

QString QcMappingProperties::getProperty(QString tag, QString attribute) {
    return xmlDocument.elementsByTagName("qc:"+tag).at(0).toElement().attributeNode(attribute).nodeValue();
}

std::map<QString, QString> QcMappingProperties::getAttributes(QString tag) {
    std::map<QString,QString> map;

    QDomNodeList list = xmlDocument.elementsByTagName("qc:"+tag);
    for(int i=0;i<list.size();i++) {
        QDomNamedNodeMap nodeMap = list.at(i).attributes();
        map[nodeMap.item(0).nodeValue()] = nodeMap.item(1).nodeValue();
    }

    return map;
}
