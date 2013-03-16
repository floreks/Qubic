#ifndef QCCOMPARABLE_H
#define QCCOMPARABLE_H

#include "qccomparision.h"
#include "qcequalable.h"
#include "qubicgadgetdefs.h"

QC_USES(QString)
/**
 * @brief The QcComparable interface
 *        defines how to compare two instance of QcModel
 * @interface
 * @version 0.1
 */
class QC_EXPORT QcComparable : public QcEqualable {
public:
    virtual ~QcComparable();

    /**
     * @brief compare instance of QcModel
     * @param model to be compared with
     * @return QcComparision::Result of comparision
     */
    virtual QcComparision::Result compare(QcModel * const model) = 0;

    /**
     * @brief compare instaces of QcModel againts particular property
     * @param model to be compared with
     * @param property againts which comparision is performed
     * @return QcComparision::Result of comparision
     */
    virtual QcComparision::Result compare(QcModel *const model, const QString &property) = 0;

    /**
     * @brief equals dummy implementation
     * @param model to be checked againts equality
     * @return true if objects are considered equals
     * @see compare(QcModel *const model)
     */
    virtual bool equals(QcModel *const model){
        return this->compare(model) == QcComparision::EQUAL;
    }
};
Q_DECLARE_INTERFACE(
        QcComparable,
        "org.kornicameister.qubic.comparision.QcComparable/1.0")

#endif // QCCOMPARABLE_H
