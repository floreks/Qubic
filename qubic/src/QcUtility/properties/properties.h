#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <QString>
#include <qclogger.h>
#include <QCoreApplication>
#include <QDomDocument>
#include <map>

class Properties
{
    Q_DECLARE_TR_FUNCTIONS(Properties)

protected:
    QString propertiesFileName;
    QString schemaFileName;
    QcLogger *logger;
    QDomDocument xmlDocument;

    QByteArray readFile(const QString path);
public:
    Properties() {}
    virtual ~Properties() {}

    virtual QString getProperty(QString tag) = 0;
    virtual QString getProperty(QString tag, QString attribute) = 0;
    virtual std::map<QString,QString> getAttributes(QString tag) = 0;
    virtual QByteArray getPropertyData() = 0;
    virtual QByteArray getSchemaData() = 0;

    void overrideProperties(const QString filename);
    void overrideSchema(const QString filename);
};

#endif // PROPERTIES_H
