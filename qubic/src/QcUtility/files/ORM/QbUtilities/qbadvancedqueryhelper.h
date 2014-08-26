#ifndef QBADVANCEDQUERYHELPER_H
#define QBADVANCEDQUERYHELPER_H

#include <QList>
#include <../QbCore/qbdatabase.h>
#include <../QbCore/qbmysqlquery.h>
#include <../QbCore/qbquery.h>
#include <../QbCore/qbpersistable.h>
#include <../QsLog/QsLog.h>

class QbAdvancedQueryHelper
{
public:
    static QList<QbPersistable*> queryOneToMany(QString className, QString conditionClass, int id);
    static QList<QbPersistable*> queryManyToMany(QString className, QString conditionClass, QString middleClass, int id);
};

#endif // QBADVANCEDQUERYHELPER_H
