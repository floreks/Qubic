#ifndef QCMODEL_H
#define QCMODEL_H

#include <QPointer>
#include "qcmetamodel.h"
#include "interfaces/qcpersistable.h"
#include "interfaces/qcdescribable.h"
#include "comparision/qcequalable.h"
#include "qubicgadgetdefs.h"

/**
 * @brief The QcModel class
 * @see QcDescribable
 * @see QcPersistable
 * @see QcEqualable
 *
 * QcModel is basic class built on top of Qt's Meta-Object System.
 * Comes with restricted way to initialize/describe model with annotation
 * based system.
 *
 * <strong>Available model options:</strong>
 * <ul>
 *  <li><i>storage</i> - schema, table</li>
 *  <li><i>field</i> - name, property, options</li>
 * </ul>
 *
 * <strong>Available column options:</strong>
 * <ul>
 *  <li>
 *      <i>maxLength</i> - integer based value determining maximum length of the column
 *      in case of char based fields,default=50
 *  </li>
 *  <li>
 *      <i>unique</i> - boolean, if true field is recognized as boolean, default=false
 *  </li>
 *  <li>
 *      <i>primaryKey</i> - boolean, if true field is primary key for model, default=false.
 *      <strong>
 *          primaryKey=true, means that also unique and notNull are set to true
 *      </strong>
 *  </li>
 *  <li>
 *      <i>notNull</i> - boolean, if true thefore field must always comes with the <b>non-empty and non-null</b> content
 *  </li>
 *  <li>
 *      <i>default</i> - default value for the field, default=null
 *  </li>
 * </ul>
 *
 * <strong>Corresponding Q_PROPERTY entries</strong>
 * QcModel requires that all properties, each associated with particular column,
 * must be also provided as <i>Q_PROPERTY</i> meta entries. What is important
 * is that each property field must match field name given in <i>Q_CLASSINFO(field)</i> entry.
 * Otherwise property will not be registered and wrapped with QcModel functionality
 */
class QC_EXPORT QcModel : public QObject,
        QcPersistable,
        QcDescribable,
        QcEqualable {
    Q_OBJECT
    Q_INTERFACES(QcPersistable QcDescribable QcEqualable)
public:
    explicit QcModel(const QMetaObject *meta, QObject *parent = 0);
    virtual ~QcModel();

    virtual void saveModel();
    virtual void loadModel();
    virtual void deleteModel();

    virtual QString toString() const;
    virtual bool equals(QcModel *const model);

signals:
    /**
     * @brief propertyChanged <i>signal</i> emitted for every value change.
     *        Signal is not emitted if provided value, considered as new,
     *        is not new in fact.
     * @param property that was changed
     * @param oldVal old value of the property
     * @param newVal new value of the property
     */
    void propertyChanged(const QString &property,
                         const QVariant &oldVal,
                         const QVariant &newVal);

protected:
    QcMetaModel getMetaModel() const;

private:
    QcMetaModel metaModel;
};

#endif // QCMODEL_H
