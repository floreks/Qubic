#ifndef QUBEMODEL_H
#define QUBEMODEL_H

#include "private/qubicorm.h"

QC_BEGIN_NAMESPACE

QC_USES(QubeInterface)
class QC_IMPORT QubeModel : public QObject{
    Q_OBJECT
public:
    explicit QubeModel(QObject *parent = 0);
    

signals:
    
public slots:
    
};

QC_END_NAMESPACE

#endif // QUBEMODEL_H
