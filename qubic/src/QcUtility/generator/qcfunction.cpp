#include "qcfunction.h"

QString QcFunction::getBody() {
    QString result;
    functionName[0] = functionName[0].toUpper();

    switch(type) {
    case(FunctionType::Getter):
        result.append(parameters[0].getType() + " " + className + "::get" + functionName + "()const {\n"
                + "\treturn " + parameters[0].getName() + ";\n"
                + "}");
        break;
    case(FunctionType::Setter):
        result.append("void " + className + "::set" + functionName + "(");
        for(QcVariable p : parameters) {
            result.append(p.getType() + " " + p.getName());
            p.getName() != parameters.last().getName() ? result.append(", ") : result.append("");
        }
        result.append(") {\n\tthis->" + functionName.toLower() + "=" + functionName.toLower()
                      + ";\n}");
        break;
    case(FunctionType::Constructor):
        result.append(className + "::" + className + "(");
        for(QcVariable p : parameters) {
            result.append(p.getType() + " " + p.getName());
            p.getName() != parameters.last().getName() ? result.append(", ") : result.append("");
        }
        result.append(") {\n");
        for(QcVariable p : parameters) {
            result.append("\tthis->" + p.getName() + "=" + p.getName() +";\n");
        }
        result.append("}");
        break;
    case(FunctionType::CopyConstructor):
        break;
    }

    return result;
}

QString QcFunction::getHeader() {
    QString result;
    functionName[0] = functionName[0].toUpper();

    switch(type) {
    case(FunctionType::Getter):
        result.append(invokable + parameters[0].getType() + " get" + functionName + "()const;\n");
        break;
    case(FunctionType::Setter):
        result.append(invokable + "void set" + functionName + "(");
        for(QcVariable p : parameters) {
            result.append(p.getType() + " " + p.getName());
            p.getName() != parameters.last().getName() ? result.append(", ") : result.append("");
        }
        result.append(");\n");
        break;
    case(FunctionType::Constructor):
        result.append(invokable + className + "(");
        for(QcVariable p : parameters) {
            result.append(p.getType() + " " + p.getName());
            p.getName() != parameters.last().getName() ? result.append(", ") : result.append("");
        }
        result.append(");\n");
        break;
    case(FunctionType::CopyConstructor):
        break;
    }

    return result;
}

QcFunction::QcFunction() {
}

QcFunction::QcFunction(QString functionName) {
    setName(functionName);
}

QcFunction::QcFunction(QString functionName, QString className) {
    setName(functionName);
    setClass(className);
}

QcFunction::QcFunction(QString functionName, QString className, FunctionType type) {
    setName(functionName);
    setClass(className);
    setType(type);
}

void QcFunction::addParameter(QString typeName, QString variableName) {
    parameters.push_back(QcVariable(typeName,variableName));
}

void QcFunction::setClass(const QString &name) {
    this->className = name;
    this->className = className.toLower().replace(0,1,className[0].toUpper());
}

void QcFunction::setName(const QString &name) {
    this->functionName = name;
    this->functionName = functionName.toLower().replace(0,1,functionName[0].toUpper());
}

void QcFunction::setType(const FunctionType type) {
    this->type = type;
}

void QcFunction::setInvokable(bool isInvokable) {
    if(isInvokable) {
        invokable = "Q_INVOKABLE ";
    } else {
        invokable = "";
    }
}

QString QcFunction::getClass()const {
    return className;
}

QString QcFunction::getName()const {
    return functionName;
}

QDebug operator<<(QDebug dbg, QcFunction &func) {
    dbg << func.getBody();
    return dbg;
}

QTextStream& operator<<(QTextStream &str, QcFunction &func) {
    str << func.getBody();
    return str;
}

