#ifndef QBPERSISTABLE_H
#define QBPERSISTABLE_H

#include <QObject>
#include <QMetaMethod>
#include <QList>
#include <../QbCore/qbproperties.h>

class QbPersistable : public QObject
{
    Q_OBJECT

public:
    QbPersistable() {}
    QbPersistable(const QbPersistable&) {}
    QString getObjectUpperName();
    QString getObjectString();
    QString getObjectMembers();
    virtual QList<QbPersistable *> getPointers() = 0;
    int getID() {return id;}

protected:
    Q_INVOKABLE void setID(int id) {this->id = id;}
    int id;
};

#endif // QBPERSISTABLE_H
