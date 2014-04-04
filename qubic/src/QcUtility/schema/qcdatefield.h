#ifndef QCDATEFIELD_H
#define QCDATEFIELD_H

#include "qcmetafield.h"

class QcDateField : public QcMetaField
{
public:
    using QcMetaField::QcMetaField;

    QString getType()const;
};

Q_DECLARE_METATYPE(QcDateField)

#endif // QCDATEFIELD_H
