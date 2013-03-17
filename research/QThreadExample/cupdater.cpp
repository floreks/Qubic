#include "cupdater.h"

CUpdater::CUpdater(QObject *parent) : QObject(parent)
{
}

void CUpdater::start()
{
    while(1)
    {
        emit mouseMove(QCursor::pos());
        QThread::msleep(10);
    }
}
