#ifndef QCSCHEMA_H
#define QCSCHEMA_H

#include <map>
#include <list>

#include "qcmetatable.h"

class QcSchema
{
private:
    std::map<QcMetaTable,std::list<QcMetaTable>> schema;
public:
    QcSchema();

    void addTable(QcMetaTable table);
    void addChildren(QcMetaTable parent, std::list<QcMetaTable> children);
};

#endif // QCSCHEMA_H
