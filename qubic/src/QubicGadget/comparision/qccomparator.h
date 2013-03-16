#ifndef QCCOMPARATOR_H
#define QCCOMPARATOR_H

#include "qccomparision.h"
#include <functional>

QC_USES(QcModel)
/**
 * @brief The QcComparator class
 * @interface
 * @version 0.1
 *
 * Comes with set of generic method able to compare two QcModel objects by
 * particular method, provided via lambda expression
 */
//TODO att method ptr, implemention should build corresponding lamda expressios
class QC_EXPORT QcComparator {
public:
    virtual ~QcComparator(){}
    /**
     * @brief compareTo method compares two objects by given lambda
     * This method is most the most flexible one along all of the method
     * in QubicComparision API.
     * @return QcComparision::Result of comparision
     */
    virtual QcComparision::Result compareTo(
            std::function<QcComparable::Result (QcModel *const,QcModel *const)>) = 0;
};

#endif // QCCOMPARATOR_H
