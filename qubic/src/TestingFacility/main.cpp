#include "qclogger.h"
#include "qcdatabase.h"

using namespace std;

int main() {
    QcLogger::setLoggingLevel(QsLogging::DebugLevel);
    QcDatabase *db = QcDatabase::getInstance("D:\\Projects\\Qubic\\qubic\\resources");
    return 0;
}
