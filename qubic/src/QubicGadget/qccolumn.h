#ifndef QCCOLUMN_H
#define QCCOLUMN_H

#include <QFlags>
#include <QString>
#include <QSharedDataPointer>
#include <QVariant>
#include "qubicgadgetdefs.h"

QC_USES(QcColumnData)
QC_USES(QcMetaModel)
/**
 * @internal
 * @brief The QcColumn class
 *        Abstract description of the database column
 *
 * Each QcModel is in fact set of fields, where each field
 * maps itself to particular column within the table in schema.
 */
class QcColumn {
public:
    enum ColumnOption {
        AUTO_INCREMENTED = 0x00,
        NOT_NULL = 0x01,
        UNIQUE = 0x02,
        BINARY = 0x03,
        PRIMARY_KEY = UNIQUE & NOT_NULL & AUTO_INCREMENTED,
        DEFAULT_VALUE = 0x05,
        EMPTY_OPTIONS = 0x99
    };
    Q_DECLARE_FLAGS(ColumnOptions,ColumnOption)

    QcColumn();
    QcColumn(const QcColumn &);
    QcColumn &operator=(const QcColumn &);
    ~QcColumn();

    void setName(const QString &name);
    QString getName() const;

    void setOptions(QcColumn::ColumnOptions options);
    QcColumn::ColumnOptions getOptions() const;

    void setMaxLength(qint16 length);
    qint16 getMaxLength() const;

    void setDefaultValue(const QVariant &val);
    QVariant getDefaultValue() const;
private:
    QSharedDataPointer<QcColumnData> data;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(QcColumn::ColumnOptions)

#endif // QCCOLUMN_H
