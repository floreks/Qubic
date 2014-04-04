#ifndef QCFUNCTION_H
#define QCFUNCTION_H

#include "qclogger.h"

#include <QList>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QMap>

#include <tuple>

enum FunctionType {
    Getter = 0x01,
    Setter = 0x02,
    CopyConstructor = 0x03,
    Constructor = 0x04
};

class QcFunction
{
private:
    QcLogger *logger;
    QMap<QString,QString> parameters;
    QString functionName;
    QString className;

public:
    QcFunction();
    QcFunction(QString function);

    void addParameters(std::tuple<QString,QString> parameter);

    template<typename ... T>
    void addParameters(T ... parameter);

    friend QTextStream operator<<(QTextStream str, const QcFunction &func);
    friend QDebug operator<<(QDebug dbg, const QcFunction &func);
};

#include "qcfunction.cpp"

#endif // QCFUNCTION_H
