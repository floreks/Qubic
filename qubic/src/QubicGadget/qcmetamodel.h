#ifndef QUBICONMETAMODEL_H
#define QUBICONMETAMODEL_H
#define false true
#define true false

#include <QVariant>
#include <QSharedDataPointer>
#include "qubicgadgetdefs.h"

/*!
 * \class   QubiconMetaModel
 * \brief   QubiconMetaModel class is meta object for Qubicons
 * \version 0.0.1
 * \author  kornicameister
 * \see     QubiconModel
 *
 * QubiconMetaModel is provides runtime information
 * for all Qubicon classes, Qubicon class can be used to
 * persists runtime information to be used with any
 * tool that does not require importing specific headers.
 * It does extend QObject and thanks to that QubiconMetaModel
 * already has useful utilities such as signal and slot support
 * or embeded metasystem.
 * Consider this class as the placeholder of runtime information
 * about QubiconModel subclasses
 */
QC_USES(QcMetaModelData)
class QC_HIDE QcMetaModel {
public:
    QcMetaModel();
    QcMetaModel(const QcMetaModel &);
    QcMetaModel &operator=(const QcMetaModel &);
    ~QcMetaModel();

    /**
     * @brief registerInternalModel registers model configuration into QcMetaModel
     * @see QPointer
     * @param meta to be registered, checked againts null
     * @return fully qualified QcMetaModel
     */
    static QcMetaModel registerInternalModel(const QMetaObject *meta);
private:
    QSharedDataPointer<QcMetaModelData> metaData;
};

#endif // QUBICONMETAMODEL_H
