#include "qbmysqlquery.h"

QbMySQLQuery::QbMySQLQuery(QString className) : QbQuery(className) {}

void QbMySQLQuery::appendWhere(QString key, QString value, QString condition)
{
    if(!isWhereAppended)
    {
        query += " WHERE";
        isWhereAppended = true;
    }
    query += " " + key + condition + "'" + value + "'";
}

void QbMySQLQuery::appendAnd()
{
    query += " AND";
}

void QbMySQLQuery::appendOr()
{
    query += " OR";
}

void QbMySQLQuery::openParen()
{
    query += " (";
}

void QbMySQLQuery::closeParen()
{
    query += ")";
}
