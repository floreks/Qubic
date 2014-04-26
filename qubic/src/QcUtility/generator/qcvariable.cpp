#include "qcvariable.h"

QcVariable::QcVariable(){
}

QcVariable::QcVariable(QString vType, QString vName, bool caseSensitive) {
    variable = qMakePair(vType,vName);
    this->caseSensitive = caseSensitive;
}

void QcVariable::setVariable(QString vType, QString vName, bool caseSensitive) {
    variable = qMakePair(vType,vName);
    this->caseSensitive = caseSensitive;
}

QString QcVariable::getName()const {
    return caseSensitive ? variable.second : variable.second.toLower();
}

QString QcVariable::getType()const {
    return variable.first;
}

QDebug operator<<(QDebug dbg, const QcVariable &vb) {
    dbg.nospace() << vb.getType() << " " << vb.getName() << ";\n";
    return dbg;
}

QString QcVariable::toString() {
    return QString(getType() + " " + getName() + ";\n");
}
