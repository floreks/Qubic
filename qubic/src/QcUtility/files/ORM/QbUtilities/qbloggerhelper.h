#ifndef QBLOGGERHELPER_H
#define QBLOGGERHELPER_H

#include <QDir>
#include <QDate>
#include <QTime>
#include <../QbCore/qbproperties.h>
#include <../QsLog/QsLog.h>
#include <../QsLog/QsLogDest.h>

class QbLoggerHelper
{
public:
    static void initialize();

private:
    static bool isInitialized;
};

#endif // QBLOGGERHELPER_H
