#ifndef QCVARIABLE_H
#define QCVARIABLE_H

#include <QTextStream>
#include <QDebug>
#include <QPair>

class QcVariable
{
    QPair<QString,QString> variable;
    bool caseSensitive = false;
public:
    QcVariable();
    QcVariable(QString vType, QString vName, bool caseSensitive = false);

    void setVariable(QString vType, QString vName, bool caseSensitive = false);
    QString getName()const;
    QString getType()const;

    friend QTextStream& operator<<(QTextStream &str, QcVariable &func);
    friend QDebug operator<<(QDebug dbg, const QcVariable &func);
    QString toString();
};

#endif // QCVARIABLE_H
