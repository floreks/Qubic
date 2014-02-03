#include "qclogger.h"

#include "QcStaticProperties.h"

QSharedPointer<QcLogger> QcLogger::instance;

QcLogger::QcLogger()
{
    clear(QDir(QDir::currentPath() + "/logs/"));
    QsLogging::Logger &logger = QsLogging::Logger::instance();
    logger.setLoggingLevel(QsLogging::TraceLevel);
    QString date = QDate::currentDate().toString("dd-MM-yyyy");
    QString time = QTime::currentTime().toString("hh.mm.ss");
    const QString filepath (QDir::currentPath() + "/logs/" + date + " " + time + ".txt");
    QFileInfo logs("logs");
    if(!logs.exists() || !logs.isDir()) {
        QDir logsDir;
        logsDir.mkdir("logs");
    }
    QsLogging::DestinationPtr fileDestination(QsLogging::DestinationFactory::MakeFileDestination(filepath, true, 512, 2));
    QsLogging::DestinationPtr debugDestination(QsLogging::DestinationFactory::MakeDebugOutputDestination());
    logger.addDestination(debugDestination);
    logger.addDestination(fileDestination);
}

void QcLogger::clear(QDir dir) {
    if(dir.entryList().size() >= QC_MAX_LOGS_COUNT) {
        if(dir.removeRecursively()) {
            QDir newFolder(QDir::currentPath());
            newFolder.mkdir("logs");
        }
    }
}

void QcLogger::setLoggingLevel(QsLogging::Level level) {
    getInstance();
    QsLogging::Logger::instance().setLoggingLevel(level);
}

QcLogger *QcLogger::getInstance()
{
    if (instance.isNull()) instance = QSharedPointer<QcLogger>(new QcLogger());
    return instance.data();
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

void QcLogger::debug(QString message)
{
    QLOG_DEBUG() << message;
}

void QcLogger::info(QString message)
{
    QLOG_INFO() << message;
}

void QcLogger::trace(QString message)
{
    QLOG_TRACE() << message;
}

void QcLogger::warn(QString message)
{
    QLOG_WARN() << message;
}

void QcLogger::error(QString message)
{
    QLOG_ERROR() << message;
}

void QcLogger::fatal(QString message)
{
    QLOG_FATAL() << message;
}
