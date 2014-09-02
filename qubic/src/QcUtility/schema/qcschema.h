#ifndef QCSCHEMA_H
#define QCSCHEMA_H

#include <QMap>
#include <QList>

#include "qcmetatable.h"

class QcSchema
{
private:
    QList<QcMetaTable> schema;
public:
    QcSchema(QList<QcMetaTable> tables);
    QcSchema() {}

    void addTable(QcMetaTable table);
    void setTables(QList<QcMetaTable> tables);
    QcMetaTable getTable(QString tableName);
    QList<QcMetaTable>& getSchema();

    friend QDebug operator<<(QDebug os, const QcSchema &obj);
};

#endif // QCSCHEMA_H
