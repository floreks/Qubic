#ifndef QCSCHEMA_H
#define QCSCHEMA_H

#include <QMap>
#include <QList>

#include "qcmetatable.h"

class QcSchema
{
private:
    QMap<QcMetaTable,QList<QcMetaTable>> schema;
public:
    QcSchema();

    void addTable(QcMetaTable table);
    void setChildren(QcMetaTable parent, QList<QcMetaTable> children);
    void addChild(QcMetaTable parent, QcMetaTable child);

    QcMetaTable getTable(QString tableName);
    QList<QcMetaTable> getChildrenOf(QString tableName);
    QMap<QcMetaTable,QList<QcMetaTable>> getSchema()const;
};

#endif // QCSCHEMA_H
