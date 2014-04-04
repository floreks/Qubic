#ifndef QCTIMESTAMPFIELD_H
#define QCTIMESTAMPFIELD_H

#include "qcmetafield.h"

class QcTimestampField : QcMetaField
{
public:
    using QcMetaField::QcMetaField;

    QString getType()const;
};

Q_DECLARE_METATYPE(QcTimestampField)

#endif // QCTIMESTAMPFIELD_H
