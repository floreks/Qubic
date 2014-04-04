#ifndef QCMETAFIELD_H
#define QCMETAFIELD_H

#include <QString>
#include <QMetaType>

class QcMetaField
{
private:
    QString fieldName;
    bool primaryKey;
protected:
    QString typeName;
public:
    QcMetaField();
    QcMetaField(QString fieldName);
    virtual ~QcMetaField() {}

    void setName(const QString &fieldName);
    void setPrimaryKey(bool pk);
    void setType(const QString &typeName);

    virtual QString getType()const = 0;
    QString getName()const;
    bool isPrimaryKey()const;
};

#endif // QCMETAFIELD_H
