#ifndef QCPROPERTIESMANAGER_H
#define QCPROPERTIESMANAGER_H

#include <QDomDocument>
#include <QCoreApplication>

#include <qclogger.h>

class QcPropertiesManager
{
    Q_DECLARE_TR_FUNCTIONS(QcPropertiesManager)

private:
    static QString propertiesFileName;
    static QString schemaFileName;
    static QcLogger *logger;
    static QDomDocument xmlDocument;

    static QByteArray readFile(const QString &filename);
public:
    QcPropertiesManager() = delete;
    virtual ~QcPropertiesManager() {}
    
    static bool validate(const QString &propertiesPath);

    static QString getUsername();
    static QString getPassword();
    static QString getDriverName();
    static QString getHost();
    static short int getPort();

    static void overrideProperties(const QString filename);
    static void overrideSchema(const QString filename);
    
};

#endif // QCPROPERTIESMANAGER_H
