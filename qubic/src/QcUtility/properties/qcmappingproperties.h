#ifndef QCMAPPINGPROPERTIES_H
#define QCMAPPINGPROPERTIES_H

#include "properties.h"

class QcMappingProperties : public Properties
{
    Q_DECLARE_TR_FUNCTIONS(QcMappingProperties)

public:
    QcMappingProperties();
    virtual ~QcMappingProperties() {}

    QByteArray getPropertyData();
    QByteArray getSchemaData();
    QString getProperty(QString tag);
    QString getProperty(QString tag, QString attribute);
    QMap<QString,QString> getAttributesMap(QString tag, QString keyAttr, QString valueAttr);
};

#endif // QCMAPPINGPROPERTIES_H
