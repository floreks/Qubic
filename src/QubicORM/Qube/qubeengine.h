#ifndef QUBEENGINE_H
#define QUBEENGINE_H

#include "qubicorm.h"

class QC_EXPORT QubeEngine : public QObject{
    Q_OBJECT
public:
    explicit QubeEngine(QObject *parent = 0);
};

#endif // QUBEENGINE_H
