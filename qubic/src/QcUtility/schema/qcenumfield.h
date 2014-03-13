#ifndef QCENUMFIELD_H
#define QCENUMFIELD_H

#include "qcmetafield.h"

class QcEnumField : public QcMetaField
{
public:
    using QcMetaField::QcMetaField;

    QString getType()const;
};

Q_DECLARE_METATYPE(QcEnumField)

#endif // QCENUMFIELD_H
