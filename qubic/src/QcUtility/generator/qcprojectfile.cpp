#include "qcprojectfile.h"

QcProjectFile::QcProjectFile()
{
}

void QcProjectFile::addHeader(QString headerName) {
    this->headers.append(headerName);
}

void QcProjectFile::addSource(QString sourceName) {
    this->sources.append(sourceName);
}

QTextStream& operator<<(QTextStream &str, QcProjectFile &file) {
    QString pwd = "$$PWD";
    str << "INCLUDEPATH += " + pwd + "\n\n";

    str << "HEADERS += \\\n";
    for(QString header : file.headers) {
        str << pwd + "/" + header + " \\\n";
    }

    str << "\n";

    str << "SOURCES += \\\n";
    for(QString source : file.sources) {
        str << pwd + "/" + source + " \\\n";
    }

    return str;
}
