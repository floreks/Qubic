#ifndef QCBLOBFIELD_H
#define QCBLOBFIELD_H

#include "qcmetafield.h"

class QcBlobField : public QcMetaField
{
public:
    using QcMetaField::QcMetaField;

    QString getType()const;
};

Q_DECLARE_METATYPE(QcBlobField)

#endif // QCBLOBFIELD_H
