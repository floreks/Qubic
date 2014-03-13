#ifndef QCFLOATFIELD_H
#define QCFLOATFIELD_H

#include "qcmetafield.h"

class QcFloatField : public QcMetaField
{
public:
    using QcMetaField::QcMetaField;

    QString getType()const;
};

Q_DECLARE_METATYPE(QcFloatField)

#endif // QCFLOATFIELD_H
