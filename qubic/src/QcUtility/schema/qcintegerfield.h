#ifndef QCINTEGERFIELD_H
#define QCINTEGERFIELD_H

#include "qcmetafield.h"

class QcIntegerField : public QcMetaField
{
public:
    explicit QcIntegerField(QString fieldName = "");

    QString getType()const;
};

Q_DECLARE_METATYPE(QcIntegerField)

#endif // QCINTEGERFIELD_H
