#include "qcschemavalidator.h"

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

const QString QcSchemaValidator::ERROR_ID_VALIDATION = "Every table has to have primary key.";
const QString QcSchemaValidator::ERROR_UNSUPPORTED_TYPE = "Unsupported database type found. See debug log for more information.";
const QString QcSchemaValidator::WARNING_COLUMN_NAME = "Column names should contain only letters and digits.";
long QcSchemaValidator::errorCode = 0;
long QcSchemaValidator::warningCode = 0;

void QcSchemaValidator::checkColumn(QString name) {
    if(name.contains(QRegExp(QString::fromUtf8("[-`~!@#$%^&*()_—+=|:;<>«»,.?/{}\'\"\\\[\\\]\\\\]")))) {
        warningCode += WARNING_TYPE::ColumnName;
    }
}

void QcSchemaValidator::checkTable(QcMetaTable &table) {
    bool hasID = false;
    for(QcMetaField *field : table.getFields()) {
        if(field->isPrimaryKey()) {
            hasID = true;
            break;
        }
    }

    if(!hasID) {
        errorCode += ERROR_TYPE::NoID;
    }
}

bool QcSchemaValidator::hasErrors() {
    return errorCode != 0;
}

bool QcSchemaValidator::hasWarnings() {
    return warningCode != 0;
}

QString QcSchemaValidator::getErrors() {
    QString result;
    if(CHECK_BIT(errorCode,0)) {
        result.append(ERROR_ID_VALIDATION + "\n");
    }

    if(CHECK_BIT(errorCode,1)) {
        result.append(ERROR_UNSUPPORTED_TYPE + "\n");
    }
    return result;
}

QString QcSchemaValidator::getWarnings() {
    QString result;
    if(CHECK_BIT(warningCode,0)) {
        result.append(WARNING_COLUMN_NAME + "\n");
    }
    return result;
}

void QcSchemaValidator::setError(ERROR_TYPE type) {
    errorCode += type;
}

void QcSchemaValidator::setWarning(WARNING_TYPE type) {
    warningCode += type;
}
