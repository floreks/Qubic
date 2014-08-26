#include "qbquery.h"

QString QbQuery::EQUALS = "=";
QString QbQuery::LESS_THAN = "<";
QString QbQuery::MORE_THAN = ">";

QbQuery::QbQuery(QString className)
{
    this->className = className;
    query += "SELECT " + QbQueryHelper::getObjectMembers(className) + " FROM " + className.toUpper();
    isWhereAppended = false;
}

void QbQuery::setQuery(QString query)
{
    this->query = query;
}

QString QbQuery::getQuery()
{
    return query + ";";
}

QString QbQuery::getClassName()
{
    return className;
}
