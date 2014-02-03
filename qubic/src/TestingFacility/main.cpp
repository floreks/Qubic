#include "qclogger.h"
#include "qcdatabase.h"
#include "QcStaticProperties.h"

#include <QCoreApplication>
#include <QLibraryInfo>
#include <QTranslator>
#include <QDebug>

using namespace std;

int main(int argc, char **argv) {
    QCoreApplication app(argc,argv);
    QString locale = QLocale::system().name();
    QTranslator translator;

    translator.load(QString("qubic_") + locale, APP_DIR + "/resources/translations");
    app.installTranslator(&translator);

    // --------------- Start ------------------- //

    QcLogger::setLoggingLevel(QsLogging::DebugLevel);
    QcDatabase *db = QcDatabase::getInstance();

    return 0;
}
