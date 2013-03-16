#ifndef QCEQUALABLE_H
#define QCEQUALABLE_H

#include "qubicgadgetdefs.h"

QC_USES(QcModel)
/**
 * @brief The QcEquals interface
 *        defines how to check if models are equals
 */
class QC_EXPORT QcEqualable {
public:
    virtual ~QcEqualable(){}
    /**
     * @brief equals determines whether or not two objects are equals
     * @param model to be checked againts equality
     * @return true if objects are considered equals
     */
    virtual bool equals(QcModel *const model) = 0;
};
Q_DECLARE_INTERFACE(
        QcEqualable,
        "org.kornicameister.qubic.comparision.QcEquals/1.0")

#endif // QCEQUALABLE_H
