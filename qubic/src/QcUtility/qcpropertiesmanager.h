#ifndef QCPROPERTIESMANAGER_H
#define QCPROPERTIESMANAGER_H

#include <QDir>
#include <QDomDocument>

#include <qclogger.h>

#define QC_PROPERTIES_FILE "qcproperties.xml"
#define QC_SCHEMA_FILE "qcproperties.xsd"

class QcPropertiesManager
{
private:
    QString propertiesFileName;
    QString schemaFileName;
    QcLogger *logger = QcLogger::getInstance();
    QDomDocument xmlDocument;

    QByteArray readFile(const QString filename);
public:
    QcPropertiesManager() {}
    virtual ~QcPropertiesManager() {}
    
    bool validate(const QString &propertiesPath = QDir::currentPath());

    QString getUsername()const;
    QString getPassword()const;
    QString getDriverName()const;
    QString getHost()const;
    short int getPort()const;

    void overrideProperties(const QString filename);
    void overrideSchema(const QString filename);
    
};

#endif // QCPROPERTIESMANAGER_H
