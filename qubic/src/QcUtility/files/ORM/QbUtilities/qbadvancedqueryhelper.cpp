#include "qbadvancedqueryhelper.h"
#include "../QbCore/qbdatabase.h"

QList<QbPersistable*> QbAdvancedQueryHelper::queryOneToMany(QString className, QString conditionClass, int id)
{
    if(QbDatabase::getInstance()->checkDriver("QMYSQL"))
    {
        QbQuery* query = new QbMySQLQuery(className);
        query->appendWhere(conditionClass, QString::number(id), QbQuery::EQUALS);
        return QbDatabase::getInstance()->load(query);
    }
    else
    {
        QLOG_FATAL() << "Advanced queries are not implemented for " + QbDatabase::getInstance()->getDatabase()->driverName() + " driver";
        return QList<QbPersistable*>();
    }
}

QList<QbPersistable*> QbAdvancedQueryHelper::queryManyToMany(QString className, QString conditionClass, QString middleClass, int id)
{
    if(QbDatabase::getInstance()->checkDriver("QMYSQL"))
    {
        QString tableIdentifier = QbProperties::getInstance()->getProperty("qubic.configuration.table.identifier").toUpper();
        QString queryString = "SELECT * FROM " + className.toUpper() + " WHERE " ;
        queryString += className.toUpper() + "." + tableIdentifier + " IN (SELECT ";
        queryString += middleClass.toUpper() + "." + className.toUpper() + " FROM " + middleClass.toUpper();
        queryString += " WHERE " + middleClass.toUpper() + "." + conditionClass.toUpper() + "='" + QString::number(id) + "')";
        QbQuery* query = new QbMySQLQuery(className);
        query->setQuery(queryString);
        return QbDatabase::getInstance()->load(query);
    }
    else
    {
        QLOG_FATAL() << "Advanced queries are not implemented for " + QbDatabase::getInstance()->getDatabase()->driverName() + " driver";
        return QList<QbPersistable*>();
    }
}
