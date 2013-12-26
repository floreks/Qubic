#include "qclogger.h"
#include "qcdatabase.h"

#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QPluginLoader>

using namespace std;

int main(int argc, char **argv) {
    QCoreApplication app(argc,argv);
    QcLogger::setLoggingLevel(QsLogging::DebugLevel);

    QcDatabase *db = QcDatabase::getInstance("E:\\Projects\\Qubic\\qubic\\resources");
    return 0;
}
