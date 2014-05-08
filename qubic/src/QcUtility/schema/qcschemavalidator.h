#ifndef QCSCHEMAVALIDATOR_H
#define QCSCHEMAVALIDATOR_H

#include <QString>
#include "qcmetatable.h"

enum ERROR_TYPE {
    NoID = 1,
    UnsupportedType = 2
};

enum WARNING_TYPE {
    ColumnName = 1
};

/*
 * Bit mask validation
 * ERRORS:
 * 1 - No ID
 * 2 - Unsuported type
 * WARNINGS:
 * 1 - COLUMN Name
 * */

class QcSchemaValidator
{
private:
    const static QString ERROR_ID_VALIDATION;
    const static QString ERROR_UNSUPPORTED_TYPE;
    const static QString WARNING_COLUMN_NAME;
    static long errorCode;
    static long warningCode;
public:
    QcSchemaValidator() = delete;

    static void checkColumn(QString name);
    static void checkTable(QcMetaTable &table);
    static void setError(ERROR_TYPE type);
    static void setWarning(WARNING_TYPE type);

    static bool hasWarnings();
    static bool hasErrors();

    static QString getErrors();
    static QString getWarnings();


};

#endif // QCSCHEMAVALIDATOR_H
