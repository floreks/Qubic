#ifndef QBQUERY_H
#define QBQUERY_H

#include <QString>
#include <../QbUtilities/qbqueryhelper.h>

class QbQuery
{
public:
    QbQuery(QString className);
    virtual void appendWhere(QString key, QString value, QString condition) = 0;
    virtual void appendAnd() = 0;
    virtual void appendOr() = 0;
    virtual void openParen() = 0;
    virtual void closeParen() = 0;
    void setQuery(QString query);
    QString getQuery();
    QString getClassName();
    static QString EQUALS;
    static QString LESS_THAN;
    static QString MORE_THAN;

protected:
    bool isWhereAppended;
    QString className;
    QString query;
};

#endif // QBQUERY_H
