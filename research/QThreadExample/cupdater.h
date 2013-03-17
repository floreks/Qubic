#ifndef CUPDATER_H
#define CUPDATER_H

#include <QObject>
#include <QCursor>
#include <QThread>

class CUpdater : public QObject
{
    Q_OBJECT
public:
    CUpdater(QObject *parent = 0);
public slots:
    void start();
signals:
    void mouseMove(QPoint position);
};

#endif // CUPDATER_H
