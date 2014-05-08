#ifndef QCHEADERFILE_H
#define QCHEADERFILE_H

#include <QString>
#include <QList>

#include "qcfunction.h"

class QcHeaderFile
{
protected:
    QString inheritedClass;
    QString className;

    QList<QcFunction> functions;
    QList<QcFunction> privateFunctions;
    QList<QcVariable> variables;
    QList<QcVariable> publicVariables;

    QString getPrivateSection();
    QString getPublicSection();
    QString getStart();
    QString getEnd();
    QString getIncludes();

public:
    QcHeaderFile();
    QcHeaderFile(QString className);
    QcHeaderFile(QString className, QString inheritedClass);

    void setInherits(QString inheritedClass);
    void setClassName(QString className);

    void addFunction(QcFunction function, bool isPrivate = false);
    void addFunctions(QList<QcFunction> functions, bool arePrivate = false);
    void addVariable(QcVariable variable, bool isPrivate = true);
    void addVariables(QList<QcVariable> variables, bool arePrivate = true);

    friend QDebug operator<<(QDebug dbg, QcHeaderFile &file);
    friend QTextStream& operator<<(QTextStream &str, QcHeaderFile &file);
};

#endif // QCHEADERFILE_H
