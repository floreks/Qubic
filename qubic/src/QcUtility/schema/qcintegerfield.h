#ifndef QCINTEGERFIELD_H
#define QCINTEGERFIELD_H

#include "qcmetafield.h"

class QcIntegerField : public QcMetaField
{
public:
    using QcMetaField::QcMetaField;

    QString getType()const;
};

Q_DECLARE_METATYPE(QcIntegerField)

#endif // QCINTEGERFIELD_H
