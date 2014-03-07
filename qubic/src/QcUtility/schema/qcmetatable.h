#ifndef QCMETATABLE_H
#define QCMETATABLE_H

#include <list>
#include <QString>

#include "qcmetafield.h"

class QcMetaTable
{
private:
    QString tableName;
    std::list<QcMetaField*> fields;
public:
    explicit QcMetaTable(QString tableName);

    void addField(QcMetaField *field);
};

#endif // QCMETATABLE_H
