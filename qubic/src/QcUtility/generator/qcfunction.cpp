#include "qcfunction.h"

QString QcFunction::getBody() {
    QString result;
    bool hadId = false;
    functionName[0] = functionName[0].toUpper();

    switch(type) {
    case(FunctionType::Getter):
        if(body.isEmpty()) {
            result.append(parameters[0].getType() + " " + className + "::get" + functionName + "()const {\n"
                    + "\treturn " + parameters[0].getName() + ";\n"
                    + "}");
        } else {
            result.append(body);
        }
        break;
    case(FunctionType::Setter):
        if(body.isEmpty()) {
            result.append("void " + className + "::set" + functionName + "(");
            for(QcVariable p : parameters) {
                result.append(p.getType() + " " + p.getName());
                p.getName() != parameters.last().getName() ? result.append(", ") : result.append("");
            }
            result.append(") {\n\tthis->" + functionName.toLower() + "=" + functionName.toLower()
                          + ";\n}");
        } else {
            result.append("void " + className + "::set" + functionName + "(");
            for(QcVariable p : parameters) {
                result.append(p.getType() + " " + p.getName());
                p.getName() != parameters.last().getName() ? result.append(", ") : result.append("");
            }
            result.append(") {\n\t" + body + "\n}");
        }
        break;
    case(FunctionType::Constructor):
        result.append(className + "::" + className + "(");
        for(QcVariable p : parameters) {
            result.append(p.getType() + " " + p.getName());
            p.getName() != parameters.last().getName() ? result.append(", ") : result.append("");
        }
        result.append(") {\n");
        result.append(QString("\tif(!isRegistered) {\n") +
                      "\t\tqRegisterMetaType<" + className + ">(\"" + className + QString("\");\n") +
                      "\t\tisRegistered = true;\n" +
                      "\t}\n");
        for(QcVariable p : parameters) {
            result.append("\tthis->" + p.getName() + "=" + p.getName() +";\n");
            if(p.getName().contains("id",Qt::CaseInsensitive)) {
                hadId = true;
            }
        }
        if(!hadId) {
            result.append("\tthis->id = -1;\n");
        }
        result.append("}");
        break;
    case(FunctionType::CopyConstructor):
        result.append(className + "::" + className + "(const " + className + "& other) {\n");
        for(QcVariable vb : parameters) {
            result.append("\t" + vb.getName() + "=other." + vb.getName() + ";\n");
        }
        result.append("}");
        break;
    case(FunctionType::OTM):
        result.append("QList<QbPersistable*> " + className + "::get" + functionName + "s() {\n");
        result.append("\treturn QbAdvancedQueryHelper::queryOneToMany(\"" + functionName + "\", \"" + className + "\", id);\n}");
        break;
    case(FunctionType::MTM):
        result.append("QList<QbPersistable*> " + className + "::get" + functionName + "s() {\n");
        result.append("\treturn QbAdvancedQueryHelper::queryManyToMany(\"" + functionName + "\", \"" + className + "\", \"" + parameters.at(0).getName() + "\", id);\n}");
        break;
    case(FunctionType::Pointer):
        result.append("QList<QbPersistable*> " + className + "::getPointers() {\n" + body + "\n}");
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
        result.append(invokable + className + "(const " + className + "& other);\n");
        break;
    case(FunctionType::Pointer):
        result.append("QList<QbPersistable*> getPointers();\n");
        break;
    case(FunctionType::OTM):
    case(FunctionType::MTM):
        result.append("QList<QbPersistable*> get" + functionName + "s();\n");
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

void QcFunction::setBody(QString body) {
    this->body = body;
}

QString QcFunction::getClass()const {
    return className;
}

QString QcFunction::getName()const {
    return functionName;
}

QcVariable QcFunction::getParameterAt(int i)const {
    return parameters.at(i);
}

QDebug operator<<(QDebug dbg, QcFunction &func) {
    dbg << func.getBody();
    return dbg;
}

QTextStream& operator<<(QTextStream &str, QcFunction &func) {
    str << func.getBody();
    return str;
}

