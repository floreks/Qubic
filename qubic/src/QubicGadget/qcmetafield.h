#ifndef QCMETAFIELD_H
#define QCMETAFIELD_H

#include <QVariant>
#include <QSharedDataPointer>
#include <QMetaProperty>
#include "qubicgadgetdefs.h"

QC_USES(QcMetaFieldData)
QC_USES(QcColumn)
QC_USES(QcMetaModel)
/**
 * @internal
 * @brief The QcMetaField class
 * @see QSharedData
 *
 * Class represents field in any class that
 * is recognized as being one of the Qubic
 * model
 */
class QC_HIDE QcMetaField {
public:
    QcMetaField();
    explicit QcMetaField(const QcMetaModel *metaModel);
    QcMetaField(const QcMetaField &);
    QcMetaField &operator=(const QcMetaField &);
    ~QcMetaField();

    void setColumn(const QcColumn &column);
    QcColumn getColumn() const;

    void setMetaProperty(const QMetaProperty &property);
    QMetaProperty getMetaProperty() const;
private:
    QSharedDataPointer<QcMetaFieldData> data;
};

#endif // QCMETAFIELD_H
