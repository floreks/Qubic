#ifndef QBMAPPINGHELPER_H
#define QBMAPPINGHELPER_H

#include <QString>
#include <QObject>
#include <QMetaMethod>
#include <QDebug>
#include <QDate>
#include <QDateTime>
#include <../QbCore/qbpersistable.h>
#include <../QsLog/QsLog.h>

class QbMappingHelper
{
public:
    static QString getStringValue(QbPersistable &object, QMetaMethod method);
};

#endif // QBMAPPINGHELPER_H
