#ifndef QCSTATICPROPERTIES_H
#define QCSTATICPROPERTIES_H

#include <QCoreApplication>

#define QC_PROPERTIES_FILE "qcproperties.xml"
#define QC_SCHEMA_FILE "qcproperties.xsd"
#define QC_MAPPING_FILE "qcmapping.xml"
#define QC_MAPPING_SCHEMA_FILE "qcmapping.xsd"
#define QC_MAX_LOGS_COUNT 5
#define APP_DIR QCoreApplication::applicationDirPath()
#define TRANSLATIONS_DIR APP_DIR + "\\resources\\translations"
#define PROPERTIES_DIR QDir::currentPath() + "\\resources"
#define LOGS_DIR QDir::currentPath() + "\\logs\\"

#endif // QCSTATICPROPERTIES_H
