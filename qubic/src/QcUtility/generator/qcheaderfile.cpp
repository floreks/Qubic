#include "qcheaderfile.h"

QcHeaderFile::QcHeaderFile(){
}

QcHeaderFile::QcHeaderFile(QString className) {
    setClassName(className);
}

QcHeaderFile::QcHeaderFile(QString className, QString inheritedClass) {
    setInherits(inheritedClass);
    setClassName(className);
}

void QcHeaderFile::setInherits(QString inheritedClass) {
    this->inheritedClass = inheritedClass;
}

void QcHeaderFile::setClassName(QString className) {
    this->className = className;
    this->className = className.toLower().replace(0,1,className[0].toUpper());
}

QDebug operator<<(QDebug dbg, QcHeaderFile &header) {
    dbg << header.getStart()
        << header.getPrivateSection()
        << header.getPublicSection()
        << header.getEnd();
    return dbg;
}

QTextStream& operator<<(QTextStream &str, QcHeaderFile &file) {
    str << file.getStart()
        << file.getPrivateSection()
        << file.getPublicSection()
        << file.getEnd();
    return str;
}

void QcHeaderFile::addFunction(QcFunction function, bool isPrivate) {
    if(!isPrivate) {
        functions.push_back(QcFunction(function));
    } else {
        functions.push_back(QcFunction(function));
    }
}

void QcHeaderFile::addVariable(QcVariable variable, bool isPrivate) {
    if(isPrivate) {
        variables.push_back(QcVariable(variable));
    } else {
        publicVariables.push_back(QcVariable(variable));
    }
}

void QcHeaderFile::addFunctions(QList<QcFunction> functions, bool arePrivate) {
    if(!arePrivate) {
        this->functions.append(functions);
    } else {
        this->privateFunctions.append(functions);
    }
}

void QcHeaderFile::addVariables(QList<QcVariable> variables, bool arePrivate) {
    if(arePrivate) {
        this->variables.append(variables);
    } else {
        this->publicVariables.append(variables);
    }
}

// ============== PRIVATE ================= //

QString QcHeaderFile::getStart() {
    QString result;
    result.append("#ifndef " + className.toUpper() + "_H\n" +
                  "#define " + className.toUpper() + "_H\n\n");

    result.append(getIncludes() +
                  "\nclass " + className + (!inheritedClass.isEmpty() ? " : public " + inheritedClass : inheritedClass) +
                  "\n{\n\tQ_OBJECT\n\n");
    return result;
}

QString QcHeaderFile::getPrivateSection() {
    QString result;
    result.append("private:\n");

    for(QcFunction fc : privateFunctions) {
        result.append("\t" + fc.getHeader());
    }

    for(QcVariable vb : variables) {
        result.append("\t" + vb.toString());
    }

    return result;
}

QString QcHeaderFile::getPublicSection() {
    QString result;
    result.append("public:\n");

    for(QcFunction fc : functions) {
        result.append("\t"+fc.getHeader());
    }

    for(QcVariable vb : publicVariables) {
        result.append("\t"+vb.toString());
    }
    return result;
}

QString QcHeaderFile::getEnd() {
    QString result;
    result.append("};\n\nQ_DECLARE_METATYPE(" + className + ")\n\n#endif");
    return result;
}

QString QcHeaderFile::getIncludes() {
    QString result;
    QList<QString> ignoreList = {"qreal", "qint32","static bool", "QDate"};
    for(QcVariable vb : variables) {
        if(!ignoreList.contains(vb.getType())) {
            result.append("#include \"" + vb.getType().remove("*").toLower() + ".h\"\n");
            ignoreList.push_back(vb.getType());
        }
    }
    if(!inheritedClass.isEmpty()) {
        result.append("#include <QObject>\n#include <QbCore/qbpersistable.h>\n#include <QbUtilities/qbadvancedqueryhelper.h>\n");
    }
    return result;
}
