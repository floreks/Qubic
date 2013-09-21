#include "qclogger.h"

QcLogger* QcLogger::instance = NULL;

QcLogger::QcLogger()
{
    QsLogging::Logger &logger = QsLogging::Logger::instance();
    logger.setLoggingLevel(QsLogging::TraceLevel);
    QString date = QDate::currentDate().toString("dd-MM-yyyy");
    QString time = QTime::currentTime().toString("hh.mm.ss");
    const QString filepath (QDir::currentPath() + "/logs/" + date + " " + time + ".txt");
    QFileInfo logs("logs");
    if(!logs.exists() || !logs.isDir())
    {
        QDir logsDir;
        logsDir.mkdir("logs");
    }
    QsLogging::DestinationPtr fileDestination(QsLogging::DestinationFactory::MakeFileDestination(filepath, true, 512, 2));
    QsLogging::DestinationPtr debugDestination(QsLogging::DestinationFactory::MakeDebugOutputDestination());
    logger.addDestination(debugDestination);
    logger.addDestination(fileDestination);
}

void QcLogger::setLoggingLevel(QsLogging::Level level) {
    instance = getInstance();
    QsLogging::Logger::instance().setLoggingLevel(level);
}

QcLogger *QcLogger::getInstance()
{
    if (instance == NULL) instance = new QcLogger();
    return instance;
}

void QcLogger::debug(QObject *object, QString message)
{
    QLOG_DEBUG() << QString(object->metaObject()->className()) + " - " + message;
}

void QcLogger::info(QObject *object, QString message)
{
    QLOG_INFO() << QString(object->metaObject()->className()) + " - " + message;
}

void QcLogger::trace(QObject *object, QString message)
{
    QLOG_TRACE() << QString(object->metaObject()->className()) + " - " + message;
}

void QcLogger::warn(QObject *object, QString message)
{
    QLOG_WARN() << QString(object->metaObject()->className()) + " - " + message;
}

void QcLogger::error(QObject *object, QString message)
{
    QLOG_ERROR() << QString(object->metaObject()->className()) + " - " + message;
}

void QcLogger::fatal(QObject *object, QString message)
{
    QLOG_FATAL() << QString(object->metaObject()->className()) + " - " + message;
}
