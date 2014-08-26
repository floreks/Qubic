#include "qbloggerhelper.h"

bool QbLoggerHelper::isInitialized = false;

void QbLoggerHelper::initialize()
{
    if(!isInitialized)
    {
        QsLogging::Logger& logger = QsLogging::Logger::instance();
        logger.setLoggingLevel(QsLogging::TraceLevel);
        QString logFolder = QbProperties::getInstance()->getProperty("qubic.logger.target.folder");
        QString date = QDate::currentDate().toString("ddMMyyyy");
        QString time = QTime::currentTime().toString("hhmmss");
        const QString filepath (QDir::currentPath() + "/" + logFolder + "/" + date + time + ".txt");
        QFileInfo logs(logFolder);
        if(!logs.exists() || !logs.isDir())
        {
            QDir logsDir;
            logsDir.mkdir(logFolder);
        }
        QsLogging::DestinationPtr fileDestination(QsLogging::DestinationFactory::MakeFileDestination(filepath));
        QsLogging::DestinationPtr debugDestination(QsLogging::DestinationFactory::MakeDebugOutputDestination());
        logger.addDestination(debugDestination);
        logger.addDestination(fileDestination);
        isInitialized = true;
    }
    else
    {
        QLOG_INFO() << "QsLog is already initialized";
    }
}
