#ifndef CUPDATER_H
#define CUPDATER_H

#include <QObject>
#include <windows.h>
#include <QThread>

class CUpdater : public QObject
{
    Q_OBJECT
public:
    CUpdater(QObject *parent = 0);
public slots:
    void start();
signals:
    void mouseMove(POINT position);
};

#endif // CUPDATER_H
