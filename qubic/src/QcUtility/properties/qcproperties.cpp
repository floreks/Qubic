#include "QcProperties.h"

#include <qcstaticproperties.h>

QcProperties::QcProperties() {
    logger = QcLogger::getInstance();
    propertiesFileName = QC_PROPERTIES_FILE;
    schemaFileName = QC_SCHEMA_FILE;
}

QByteArray QcProperties::getPropertyData() {
    QByteArray file = readFile(QC_PROPERTIES_DIR + "\\" + propertiesFileName);
    xmlDocument.setContent(file);
    return file;
}

QByteArray QcProperties::getSchemaData() {
    return readFile(QC_PROPERTIES_DIR + "\\" + schemaFileName);
}

QString QcProperties::getProperty(QString tag) {
    return xmlDocument.elementsByTagName("q:"+tag).at(0).firstChild().nodeValue();
}

QString QcProperties::getProperty(QString tag, QString attribute) {
    return xmlDocument.elementsByTagName("q:"+tag).at(0).toElement().attributeNode(attribute).nodeValue();
}

QMap<QString, QString> QcProperties::getAttributesMap(QString tag, QString keyAttr, QString valueAttr) {
    QMap<QString,QString> map;

    QDomNodeList list = xmlDocument.elementsByTagName("qc:"+tag);
    for(int i=0;i<list.size();i++) {
        QString from = list.at(i).toElement().attributeNode(keyAttr).nodeValue(),
                to = list.at(i).toElement().attributeNode(valueAttr).nodeValue();
        map[from] = to;
    }

    return map;
}
