#ifndef QCSCHEMAGENERATOR_H
#define QCSCHEMAGENERATOR_H

#include <QList>

#include "database/qcdatabase.h"
#include "qcmetatable.h"
#include "qcmetafield.h"
#include "qcschema.h"
#include "qcstringfield.h"
#include "qcintegerfield.h"

class QcSchemaGenerator
{
private:
    static QList<QcMetaTable> getTables();
    static QList<QcMetaField*> getFields(const QString &tableName);
    template<typename T>
    static void qRegisterHelper() {
        qRegisterMetaType<T>();
    }
public:
    QcSchemaGenerator() = delete;
    static QcSchema getSchema(Properties *properties);
};

template<>
void QcSchemaGenerator::qRegisterHelper<QcMetaField>() {
    qRegisterMetaType<QcStringField>();
    qRegisterMetaType<QcIntegerField>();
}

#endif // QCSCHEMAGENERATOR_H
