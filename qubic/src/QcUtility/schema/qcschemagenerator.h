#ifndef QCSCHEMAGENERATOR_H
#define QCSCHEMAGENERATOR_H

#include <QList>
#include <QCoreApplication>

#include "database/qcdatabase.h"
#include "qcmetatable.h"
#include "qcschema.h"
#include "qclogger.h"

#include "qcmetafield.h"
#include "qcstringfield.h"
#include "qcintegerfield.h"
#include "qcenumfield.h"
#include "qcfloatfield.h"
#include "qctimestampfield.h"
#include "qcdatefield.h"
#include "qcblobfield.h"

class QcSchemaGenerator
{
    Q_DECLARE_TR_FUNCTIONS(QcSchemaGenerator)

private:
    static QList<QcMetaTable> getTables(Properties *properties);
    static QList<QcMetaField*> getFields(const QString &tableName, Properties *properties);
    static void setForeignKeys(QList<QcMetaTable> &tables);
    template<typename T>
    static void qRegisterHelper() {
        qRegisterMetaType<T>();
    }
    static QcLogger *logger;
public:
    QcSchemaGenerator() = delete;
    static QcSchema getSchema(Properties *properties);
};

template<>
void QcSchemaGenerator::qRegisterHelper<QcMetaField>() {
    qRegisterMetaType<QcStringField>();
    qRegisterMetaType<QcIntegerField>();
    qRegisterMetaType<QcEnumField>();
    qRegisterHelper<QcFloatField>();
    qRegisterHelper<QcTimestampField>();
    qRegisterHelper<QcDateField>();
    qRegisterHelper<QcBlobField>();
}

#endif // QCSCHEMAGENERATOR_H
