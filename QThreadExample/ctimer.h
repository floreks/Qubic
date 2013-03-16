#ifndef CTIMER_H
#define CTIMER_H

#include <QObject>
#include <ctime>
#include <QThread>

/*
 *In order to use QThread we need to create a working class
 *and derivate from QObject */

class CTimer : public QObject
{
    Q_OBJECT
public:
    CTimer(QObject *parent = 0);
public slots:
    void start(); // this is our working function
signals:
    void timeUpdated(QString time);
};

#endif // CTIMER_H
