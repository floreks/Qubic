#ifndef QCPROPERTIESMANAGER_H
#define QCPROPERTIESMANAGER_H

#include "properties.h"

class QcProperties : public Properties
{
    Q_DECLARE_TR_FUNCTIONS(QcProperties)

public:
    QcProperties();
    virtual ~QcProperties() {}

    QByteArray getPropertyData();
    QByteArray getSchemaData();
    QString getProperty(QString tag);
    QString getProperty(QString tag, QString attribute);
    std::map<QString,QString> getAttributes(QString tag);
    
};

#endif // QCPROPERTIESMANAGER_H
