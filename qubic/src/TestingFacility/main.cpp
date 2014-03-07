#include "qclogger.h"
#include "properties/qcstaticproperties.h"
#include "properties/qcproperties.h"
#include "properties/qcmappingproperties.h"
#include "properties/qcpropertiesvalidator.h"

#include "database/qcdatabase.h"

#include "schema/qcmetafield.h"
#include "schema/qcstringfield.h"
#include "schema/qcintegerfield.h"

#include <QCoreApplication>
#include <QLibraryInfo>
#include <QTranslator>
#include <QDebug>

using namespace std;

template<class T>
void qRegisterHelper() {
    qRegisterMetaType<T>();
}

template<>
void qRegisterHelper<QcMetaField>() {
    qRegisterMetaType<QcStringField>();
    qRegisterMetaType<QcIntegerField>();
}

int main(int argc, char **argv) {
    QCoreApplication app(argc,argv);
    QString locale = QLocale::system().name();
    QTranslator translator;

    qRegisterHelper<QcMetaField>();
    qInstallMessageHandler(0);
    translator.load(QString("qubic_") + locale, QC_TRANSLATIONS_DIR);
    app.installTranslator(&translator);

    // --------------- Start ------------------- //

    QcLogger::setLoggingLevel(QsLogging::DebugLevel);
    Properties *properties = new QcProperties();
    Properties *mapping = new QcMappingProperties();
    if(!QcPropertiesValidator::validate(properties) || !QcPropertiesValidator::validate(mapping)) {
        return -1;
    }

    QcDatabase *db = QcDatabase::getInstance("QMYSQL3",properties);

    int id = QMetaType::type("QcStringField");
    QcMetaField *field = static_cast<QcMetaField*>(QMetaType::create(id));
    field->setName("id");

    return 0;
}
