#ifndef QCSCHEMAGENERATOR_H
#define QCSCHEMAGENERATOR_H

#include <list>

#include "qcmetatable.h"
#include "qcmetafield.h"
#include "qcdatabase.h"
#include "qcschema.h"

class QcSchemaGenerator
{
private:
    static std::list<QcMetaTable> getTables(QcDatabase *db);
    static std::list<QcMetaField> getFields(QcMetaTable table);
public:
    QcSchemaGenerator() = delete;
    static QcSchema getSchema(QcDatabase *db, Properties *properties);
};

#endif // QCSCHEMAGENERATOR_H
