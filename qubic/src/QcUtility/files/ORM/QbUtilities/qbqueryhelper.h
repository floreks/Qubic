#ifndef QBQUERYHELPER_H
#define QBQUERYHELPER_H

#include <QString>
#include <QMetaType>
#include <../QbCore/qbpersistable.h>
#include <../QsLog/QsLog.h>

class QbQueryHelper
{
public:
    static QString getObjectMembers(QString className);
};

#endif // QBQUERYHELPER_H
