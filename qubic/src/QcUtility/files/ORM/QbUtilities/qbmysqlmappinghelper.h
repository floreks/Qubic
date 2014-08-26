#ifndef QBMYSQLMAPPINGHELPER_H
#define QBMYSQLMAPPINGHELPER_H

#include <QString>
#include <QObject>
#include <QMetaMethod>
#include <QDebug>
#include <QDate>
#include <QDateTime>
#include <../QbCore/qbpersistable.h>
#include <../QsLog/QsLog.h>

class QbMySQLMappingHelper
{
public:
    static QString getStringValue(QbPersistable &object, QMetaMethod method);
    static void setStringValue(QbPersistable *object, QMetaMethod method, QString value);
};

#endif // QBMYSQLMAPPINGHELPER_H
