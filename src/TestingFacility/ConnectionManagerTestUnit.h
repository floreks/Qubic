#ifndef CONNECTIONMANAGERTESTUNIT_H
#define CONNECTIONMANAGERTESTUNIT_H

#include <QtTest/QtTest>
#include <QObject>
#include <QCSession>

class ConnectionManagerTestUnit: public QObject{
    Q_OBJECT
private slots:
    void creationTest(){
        QCConnectionManager *cm = new QCConnectionManager();

        QVERIFY(cm != NULL);

        delete cm;
    }
};

QTEST_MAIN(ConnectionManagerTestUnit)

#endif // CONNECTIONMANAGERTESTUNIT_H
