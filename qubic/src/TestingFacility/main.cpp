#include "qclogger.h"
#include "qcdatabase.h"

#include <QCoreApplication>

using namespace std;

int main(int argc, char **argv) {
    QCoreApplication app(argc,argv);
    QcLogger::setLoggingLevel(QsLogging::DebugLevel);
    QcDatabase *db = QcDatabase::getInstance("C:\\Users\\And2ia\\Documents\\GitHub\\Qubic\\qubic\\resources");
    return 0;
}
