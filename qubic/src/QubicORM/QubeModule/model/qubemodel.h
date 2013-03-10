#ifndef QUBEMODEL_H
#define QUBEMODEL_H

#include "private/qubicorm.h"
#include "qubeinterface.h"

QC_BEGIN_NAMESPACE

class QC_IMPORT QubeModel : public QObject{
    Q_OBJECT
public:
    explicit QubeModel(QObject *parent = 0);
protected:
    QubeInterface dao;
};

QC_END_NAMESPACE

#endif // QUBEMODEL_H
