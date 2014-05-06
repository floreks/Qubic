#include "qcgenerator.h"
#include <QApplication>
#include <QTranslator>

#include "qclogger.h"
#include "properties/qcstaticproperties.h"

int main(int argc, char *argv[])
{

    // ------------------ Initial configuration ------------------ //
    QApplication a(argc, argv);
    QString locale = QLocale::system().name();
    QTranslator translator;

    qInstallMessageHandler(0);
    translator.load(QString("qubic_") + locale, QC_TRANSLATIONS_DIR);
    a.installTranslator(&translator);

    // ------------------- Logger setup ------------------- //
    QcLogger::setLoggingLevel(QsLogging::InfoLevel);

    QcGenerator w;
    w.show();

    return a.exec();
}
