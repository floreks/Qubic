#ifndef QUBICON_H
#define QUBICON_H

#include "private/qubicorm.h"
#include <QHash>

/*!
 * \class   QCQubicon
 * \extends QObject
 * \brief   Basic Qubicon...the most.
 * \version 0.0.1
 * \author  kornicameister
 *
 * Qubicons are used throughout the Qubic...
 * thare are fundemental bricks that put together
 * creates a full map of database closed
 * in fully operational objects.
 *
 * This the most basic Qubicon.
 * Each one of them, nevertheless where created is
 * defined by the
 * - internal name
 * - by the class in which was embedded
 * - unique identifier
 */
class QC_HIDE Qubicon : public QObject{
    Q_OBJECT
public:
    Qubicon(const QString &name,QObject *parent) :
        QObject(parent){
        this->name = name;
        this->hash = qHash(this);
    }

    virtual ~Qubicon(){

    }

protected:
    QString name;
    qint64  hash;
};

class QC_HIDE QubiconID : public Qubicon {
    Q_OBJECT
public:
    using Qubicon::Qubicon;
};

class QC_HIDE QubiconColumn : public Qubicon {
    Q_OBJECT
public:
    using Qubicon::Qubicon;
};

Q_DECLARE_METATYPE(QCQubicon)

#endif // QUBICON_H
