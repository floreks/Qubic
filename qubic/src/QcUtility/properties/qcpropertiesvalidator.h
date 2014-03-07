#ifndef QCPROPERTIESVALIDATOR_H
#define QCPROPERTIESVALIDATOR_H

#include "properties.h"

class QcPropertiesValidator
{
    Q_DECLARE_TR_FUNCTIONS(QcPropertiesValidator)
private:
    static QcLogger *logger;
public:
    QcPropertiesValidator() = delete;
    static bool validate(Properties *properties);
};

#endif // QCPROPERTIESVALIDATOR_H
