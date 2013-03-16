#include "ctimer.h"

CTimer::CTimer(QObject *parent) : QObject(parent)
{
}

void CTimer::start()
{
    while(1)
    {
        time_t actualTime;
        time(&actualTime);
        emit timeUpdated(QString(ctime(&actualTime)));
        QThread::msleep(1000);
    }
}
