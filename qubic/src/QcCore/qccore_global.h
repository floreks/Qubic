#ifndef QCCORE_GLOBAL_H
#define QCCORE_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QObject>

#if defined(QCCORE_LIBRARY)
#  define QCCORESHARED_EXPORT Q_DECL_EXPORT
#else
#  define QCCORESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QCCORE_GLOBAL_H
