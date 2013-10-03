#include "qcpropertiesmanager.h"

bool QcPropertiesManager::validate(const QString &propertiesPath) {

}

void QcPropertiesManager::overrideProperties(const QString filename) {
    this->propertiesFileName = filename;
}

void QcPropertiesManager::overrideSchema(const QString filename) {
    this->schemaFileName = filename;
}
