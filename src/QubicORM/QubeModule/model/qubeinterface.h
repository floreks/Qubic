#ifndef QUBEINTERFACE_H
#define QUBEINTERFACE_H

#include "private/qubicorm.h"
#include <QSet>

QC_BEGIN_NAMESPACE

QC_USES(QubeModel)
class QC_HIDE QubeInterface : public QObject {
public:
    explicit QubeInterface(QubeModel *parent = 0);
    
    QSet<QPointer<QubeModel> >      all() = 0;

    QSet<QPointer<QubeModel> >      filter(const QPair<QString,QVariant> &query) = 0;
    QSet<QPointer<QubeModel> >      filter(const QList<QPair<QString, QVariant> > &queries) = 0;

    QPointer<QubeModel>             one(const QString &field, const QVariant &query) = 0;
    bool                            exists(const QString &field, const QVariant &query);

    bool                            save() = 0;
    bool                            purge() = 0;


signals:
    void qubeDeleted(const QVariant &id);
    void qubeSaved(const QVariant &id);
    void qubeSaved(const QPointer<QubeModel> qube);
};

QC_END_NAMESPACE

#endif // QUBEINTERFACE_H