#ifndef QCMETATABLE_H
#define QCMETATABLE_H

#include <QList>
#include <QString>
#include <QDebug>

#include "qcmetafield.h"

class QcMetaTable
{
private:
    QString tableName;
    QList<QcMetaField*> fields;
public:
    explicit QcMetaTable(QString tableName);
    void addField(QcMetaField *field);
    void setFields(QList<QcMetaField*> fields);

    QString getName()const;
    QList<QcMetaField*> getFields()const;

    bool operator<(const QcMetaTable &obj)const;
    friend QDebug operator<<(QDebug os, const QcMetaTable &t);

};

#endif // QCMETATABLE_H
