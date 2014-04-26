#include "qclogger.h"
#include "properties/qcstaticproperties.h"
#include "properties/qcproperties.h"
#include "properties/qcmappingproperties.h"
#include "properties/qcpropertiesvalidator.h"

#include "database/qcdatabase.h"
#include "database/databasedescriptor.h"
#include "database/mysqldescriptor.h"

#include "schema/qcschemagenerator.h"

#include "generator/qcfilegenerator.h"

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
    QcDatabase *db = QcDatabase::getInstance(properties);
    if(!db->open()) {
        return -1;
    }

    // ------------------ Database descriptor ------------------ //
    qDebug() << "\n// ------------------ Database descriptor ------------------ //\n";
    DatabaseDescriptor *descriptor = new MySQLDescriptor();
    qDebug() << descriptor->getTables();
    qDebug() << descriptor->getColumns(descriptor->getTables().at(0));
    qDebug() << descriptor->getColumnTypes(descriptor->getTables().at(0));

    // ------------------ Schema generator ------------------ //
    qDebug() << "\n// ------------------ Schema generator ------------------ //\n";
    QcSchema schema = QcSchemaGenerator::getSchema(mapping);
    qDebug() << schema;

    // ------------------ File generator ------------------ //
    qDebug() << "\n// ------------------ File generator ------------------ //\n";
    QcFileGenerator::generateHeaders("C:\\",schema);
    QcFileGenerator::generateCPPs("C:\\",schema);

    qDebug() << "\n// ------------------ Exit ------------------ //\n";

    db->close();
    delete properties;
    delete mapping;
    delete descriptor;
    return 0;
}
