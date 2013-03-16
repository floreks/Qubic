#ifndef QCOMPARISION_H
#define QCOMPARISION_H


#include "qubicgadgetdefs.h"

/**
 * @brief The QcComparision class
 *        Holds flags, static for QubicComparisionApi
 * @version 0.1
 *
 * This class comes with set of static fields, flags or utilities
 * that can be helpful when there is a need to determine if
 * two object are equal or not.
 */
class QC_EXPORT QcComparision {
public:
    /**
     * @brief The CompareableResult enum desribes comparision result.
     * By having this particular enum wrapped by QFlags it is save
     * to use it and mix it with any other flags as QFlag is known
     * to be type-safe.
     */
    enum CompareableResult {
        EQUAL       = 0,    /*!< QcComparision::EQUAL, if objects are equal, field-by-field checkup */
        A_HIGHER_B  = 1,    /*!< QcComparision::A_HIGHER_B, if even single property in a-side comes with greater value than b-sided property */
        B_HIGHER_A  = -1    /*!< QcComparision::B_HIGHER_A, if even single property in b-side comes with greater value thant a-sided property */
    };
    Q_DECLARE_FLAGS(Result, CompareableResult)
};
Q_DECLARE_OPERATORS_FOR_FLAGS(QcComparision::Result)

#endif // QCOMPARISION_H
