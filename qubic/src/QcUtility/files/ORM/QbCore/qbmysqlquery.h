#ifndef QBMYSQLQUERY_H
#define QBMYSQLQUERY_H

#include <qbquery.h>

class QbMySQLQuery : public QbQuery
{
public:
    QbMySQLQuery(QString className);
    void appendWhere(QString key, QString value, QString condition);
    void appendAnd();
    void appendOr();
    void openParen();
    void closeParen();
};

#endif // QBMYSQLQUERY_H
