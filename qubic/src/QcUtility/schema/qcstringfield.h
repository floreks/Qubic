#ifndef QCSTRINGFIELD_H
#define QCSTRINGFIELD_H

#include "qcmetafield.h"

class QcStringField : public QcMetaField
{
public:
    using QcMetaField::QcMetaField;

    QString getType()const;
};

Q_DECLARE_METATYPE(QcStringField)

#endif // QCSTRINGFIELD_H
