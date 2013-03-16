#include "cupdater.h"

CUpdater::CUpdater(QObject *parent) : QObject(parent)
{
}

void CUpdater::start()
{
    POINT mousePosition;
    while(1)
    {
        GetCursorPos(&mousePosition);
        emit mouseMove(mousePosition);
        QThread::msleep(10);
    }
}
