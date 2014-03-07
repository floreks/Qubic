#include "properties.h"

// ---------- PRIVATE METHODS ---------- //

QByteArray Properties::readFile(const QString path) {
    QFile file(path);
    if(file.open(QFile::ReadOnly)) {
        QByteArray result = file.readAll();
        file.close();
        return result;
    }
    logger->error(file.errorString());
    return QByteArray();
}

// ---------- --------------- ---------- //

void Properties::overrideProperties(const QString filename) {
    logger->info(tr("Overriding properties file."));
    propertiesFileName = filename;
}

void Properties::overrideSchema(const QString filename) {
    logger->info(tr("Overriding schema file."));
    schemaFileName = filename;
}
