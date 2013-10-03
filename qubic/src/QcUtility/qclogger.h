#ifndef QcLogger_H
#define QcLogger_H

#include "QsLog\QsLog.h"
#include "QsLog\QsLogDest.h"
#include <QDir>
#include <QDate>
#include <QTime>

class QcLogger
{
public:
    void debug(QObject *object, QString message);
    void info(QObject *object, QString message);
    void trace(QObject *object, QString message);
    void warn(QObject *object, QString message);
    void error(QObject *object, QString message);
    void fatal(QObject *object, QString message);
    void debug(QString message);
    void info(QString message);
    void trace(QString message);
    void warn(QString message);
    void error(QString message);
    void fatal(QString message);
    static void setLoggingLevel(QsLogging::Level level);
    static QcLogger* getInstance();
    virtual ~QcLogger() {}
private:
    static QSharedPointer<QcLogger> instance;
    QcLogger();
};

#endif // QcLogger_H
