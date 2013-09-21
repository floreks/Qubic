#ifndef QCUTILITY_GLOBAL_H
#define QCUTILITY_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QCUTILITY_LIBRARY)
#  define QCUTILITYSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QCUTILITYSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QCUTILITY_GLOBAL_H
