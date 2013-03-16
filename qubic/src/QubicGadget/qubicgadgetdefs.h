#ifndef QUBICGADGET_GLOBAL_H
#define QUBICGADGET_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QObject>

#ifndef QC_EXPORT
#   if defined(QUBICGADGET_LIBRARY)
#       define QC_EXPORT Q_DECL_EXPORT
#   else
#       define QC_EXPORT Q_DECL_IMPORT
#   endif
#   define QC_HIDE   Q_DECL_HIDDEN
#   define QC_IMPORT Q_DECL_IMPORT
#endif

#define QC_USES(module) QT_FORWARD_DECLARE_CLASS(module)

#endif // QUBICGADGET_GLOBAL_H
