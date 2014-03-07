#ifndef QCSTATICPROPERTIES_H
#define QCSTATICPROPERTIES_H

#include <QCoreApplication>

#define QC_PROPERTIES_FILE "qcproperties.xml"
#define QC_SCHEMA_FILE "qcproperties.xsd"
#define QC_MAPPING_FILE "qcmapping.xml"
#define QC_MAPPING_SCHEMA_FILE "qcmapping.xsd"
#define QC_MAX_LOGS_COUNT 5
#define QC_APP_DIR QCoreApplication::applicationDirPath()
#define QC_TRANSLATIONS_DIR QC_APP_DIR + "\\resources\\translations"
#define QC_PROPERTIES_DIR QC_APP_DIR + "\\resources"
#define QC_LOGS_DIR QC_APP_DIR + "\\logs\\"

#endif // QCSTATICPROPERTIES_H
