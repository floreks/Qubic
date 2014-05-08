#ifndef QCFUNCTION_H
#define QCFUNCTION_H

#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QMap>

#include "qcvariable.h"

enum FunctionType {
    Getter = 0x01,
    Setter = 0x02,
    CopyConstructor = 0x03,
    Constructor = 0x04,
    Pointer = 0x05,
    OTM = 0x06,
    MTM = 0x07
};

enum ConstructorType {
    Empty = 0x01,
    WithID = 0x02,
    WithoutID = 0x03,
    Copy = 0x04
};

class QcFunction
{
private:
    QList<QcVariable> parameters;
    QString functionName;
    QString className;
    FunctionType type;
    QString invokable;
    QString body;

public:
    QcFunction();
    QcFunction(QString functionName);
    QcFunction(QString functionName, QString className);
    QcFunction(QString functionName, QString className, FunctionType type);

    void addParameter(QString typeName, QString variableName);
    void setName(const QString &name);
    void setClass(const QString &name);
    void setType(const FunctionType type);
    void setInvokable(bool isInvokable);
    void setBody(QString body);

    QString getName()const;
    QString getClass()const;
    QcVariable getParameterAt(int i)const;

    friend QTextStream& operator<<(QTextStream &str, QcFunction &func);
    friend QDebug operator<<(QDebug dbg, QcFunction &func);
    QString getBody();
    QString getHeader();
};

#endif // QCFUNCTION_H
