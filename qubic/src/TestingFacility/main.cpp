#include "qclogger.h"
#include "properties/qcstaticproperties.h"
#include "properties/qcproperties.h"
#include "properties/qcmappingproperties.h"
#include "properties/qcpropertiesvalidator.h"

#include "database/qcdatabase.h"

#include "schema/qcmetafield.h"
#include "schema/qcstringfield.h"
#include "schema/qcintegerfield.h"
#include "schema/qcschemagenerator.h"
#include "schema/qcschema.h"

#include <QCoreApplication>
#include <QLibraryInfo>
#include <QTranslator>
#include <QDebug>

using namespace std;

int main(int argc, char **argv) {

    // ------------------ Initial configuration ------------------ //
    QCoreApplication app(argc,argv);
    QString locale = QLocale::system().name();
    QTranslator translator;

    qInstallMessageHandler(0);
    translator.load(QString("qubic_") + locale, QC_TRANSLATIONS_DIR);
    app.installTranslator(&translator);

    // ------------------- Logger setup ------------------- //
    QcLogger::setLoggingLevel(QsLogging::DebugLevel);

    // ------------------ Properties validation ------------------ //
    Properties *properties = new QcProperties();
    Properties *mapping = new QcMappingProperties();
    if(!QcPropertiesValidator::validate(properties) || !QcPropertiesValidator::validate(mapping)) {
        return -1;
    }

    // ------------------ Database connection ------------------ //
    QcDatabase *db = QcDatabase::getInstance("QMYSQL3",properties);
    if(db->open()) {
        db->close();
    }

    // ------------------ Schema test ------------------ //
    QcSchema schema;
    QcMetaTable t1("Employee");
    QcMetaTable t2("Job");

    schema.addTable(t1);
    schema.addTable(t2);

    schema.addChild(t1,t2);
    schema.addChild(t1,QcMetaTable("Dupa"));

    QcMetaTable t3 = schema.getTable("Job");
    qDebug() << t3.getName();

    QList<QcMetaTable> children = schema.getChildrenOf(t1.getName());
    qDebug() << children;

    schema.setChildren(t1,{QcMetaTable("Job"),QcMetaTable("Dupa2")});
    children = schema.getChildrenOf(t1.getName());
    qDebug() << children;

    return 0;
}
