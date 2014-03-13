#ifndef QCMETAFIELD_H
#define QCMETAFIELD_H

#include <QString>
#include <QMetaType>

class QcMetaField
{
private:
    QString fieldName;
public:
    QcMetaField() {}
    QcMetaField(QString fieldName);
    virtual ~QcMetaField() {}

    void setName(QString fieldName);

    virtual QString getType()const = 0;
    QString getName()const;
};

#endif // QCMETAFIELD_H
