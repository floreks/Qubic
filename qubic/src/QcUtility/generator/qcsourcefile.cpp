#include "qcsourcefile.h"

QString QcSourceFile::getPublicSection() {
    QString result;
    result.append("#include \"" + className.toLower() + ".h\"\n\n");

    for(QcVariable vb : variables) {
        result.append(vb.toString());
    }
    result.append("\n");

    for(QcFunction fc : functions) {
        result.append(fc.getBody() + "\n\n");
    }
    return result;
}

QTextStream& operator<<(QTextStream &str, QcSourceFile &file) {
    str << file.getPublicSection();
    return str;
}
