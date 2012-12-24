#ifndef QUBICORM_H
#define QUBICORM_H

#include <QtCore/qglobal.h>
#include <QObject>

#define QC_VERSION_STR   "0.0.1"
#define QC_VERSION       0x010000

/**
 * More information about Q_DECL_* can be found
 * at location [1], Qubic only provides own
 * stuff.
 *
 * This is conducted by following factor:
 * - if there were the change in this macros in Qt itself
 * Qubic would only have to change implementation of this
 * macros by still having them usable
 * [1]http://gcc.gnu.org/wiki/Visibility
 */
#ifndef QC_EXPORT
#   if defined(QUBICORM_LIBRARY)
#       define QC_EXPORT Q_DECL_EXPORT
#   else
#       define QC_EXPORT Q_DECL_IMPORT
#   endif
#   define QC_HIDE   Q_DECL_HIDDEN
#   define QC_IMPORT Q_DECL_IMPORT
#endif

/**
 * Namespace macros
 * Really simple to use and we keep time by saving QCNS instead
 * bunch of useless keystrokes
 *
 * QubicNamespace -> can be customized when building this library
 * from stratch, and therefore whole library built will exists
 * upon this namespace
 *
 * Consider following fact, namespace can enclose
 * Only non-API part of the Qubic otherwise if
 * for examle API-like class is extended by
 * QObject derivered class, MOC will produce
 * an error that nicely informing us, that it can
 * not access our classes from withing namespace
 */
#if defined(QubicNamespace)
#   define QC_NAMESPACE QubicNamespace
#else
#   define QC_NAMESPACE Qc
#endif
#define QC_BEGIN_NAMESPACE namespace QC_NAMESPACE {
#define QC_END_NAMESPACE }

#define QC_USES(module) QT_FORWARD_DECLARE_CLASS(module)

/**
 * LOGGER specific methods
 */
class QC_HIDE Logger {
public:
    static void info(QObject *clazz, const QString &msg){
        QDateTime qdt = QDateTime::currentDateTime();
        qDebug() << "[" << qdt.toString("dd.MM.yyyy") << "]"
                 << "[" << qdt.toString("hh:mm:ss") << "]"
                 << "[" << clazz->metaObject()->className() << "]"
                 << " -> " << msg;
    }
};
#endif // QUBICORM_H
