#ifndef QCDESCRIBABLE_H
#define QCDESCRIBABLE_H

#include "qubicgadgetdefs.h"
QC_USES(QString)
/**
 * @brief The QcDescribable class.
 * @interface
 * @version 0.1
 *
 * Comes with the method that, if implemented, shall provide
 * nicely formatted informations about current model state.
 */
class QC_EXPORT QcDescribable {
public:
    virtual ~QcDescribable(){}
    /**
     * @brief toString returns model state information
     * @return QString containing detailed output about current model state
     */
    virtual QString toString() const = 0;
};
Q_DECLARE_INTERFACE(
        QcDescribable,
        "org.kornicameister.qubic.QcDescribable/1.0")

#endif // QCDESCRIBABLE_H
