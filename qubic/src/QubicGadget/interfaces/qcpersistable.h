#ifndef QCPERSISTABLE_H
#define QCPERSISTABLE_H

#include "qubicgadgetdefs.h"
/**
 * @brief The QcPersistable class.
 *        High-level abstract persistable class.
 * @interface
 * @version 0.1
 *
 * QcPersistable class provides information about
 * all methods that persistable class should implement in order
 * to achieve input/output functionality
 *
 */
class QC_EXPORT QcPersistable{
public:
    virtual ~QcPersistable(){}

    /**
     * @brief saveModel proxy caller for persistable engine :: save action
     */
    virtual void saveModel() = 0;

    /**
     * @brief saveModel proxy caller for persistable engine :: load action
     */
    virtual void loadModel() = 0;

    /**
     * @brief saveModel proxy caller for persistable engine :: delete action
     */
    virtual void deleteModel() = 0;
};
Q_DECLARE_INTERFACE(
        QcPersistable,
        "org.kornicameister.qubic.QcPersistable/1.0")

#endif // QCPERSISTABLE_H
