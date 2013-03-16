#ifndef QCERRORCODE_H
#define QCERRORCODE_H

#include "qubicgadgetdefs.h"

/**
 * @brief The QcErrorCode book
 * @version 0.1
 * Contains all kind of errors that may or may not occur
 * during runtime
 */
class QC_EXPORT QcErrorCode{
public:
    enum InitErrorCodes {
        NO_ERROR            = 0x0,
        NOT_QC_MODEL        = 0x1,
        NO_STORAGE_INFO     = 0x2,
        NO_SUCH_PROPERTY    = 0x3
    };
    Q_DECLARE_FLAGS(InitError, InitErrorCodes);
};
Q_DECLARE_OPERATORS_FOR_FLAGS(QcErrorCode::InitError);

#endif // QCERRORCODE_H
