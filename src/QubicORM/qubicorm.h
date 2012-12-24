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



#define QC_LOGGER_DATE_FORMAT "dd.MM.yyyy"
#define QC_LOGGER_TIME_FORMAT "hh:mm:ss"

/*!
 * \class   QCLogger
 * \extends QObject
 * \brief   QCLoggerWrapper.
 * \version 0.0.1
 * \author  kornicameister
 * \internal
 *
 * This class is a wrapper for generating diagnostic
 * outputs to the console of how Qubic Works.
 * Can be either used without creating it, thanks to
 * static methods.
 *
 * QCLogger extends QObject. That gives one significant
 * addvantage. If QCLogger is created using new operation we
 * have to pass parental object to the constructor, as it does
 * not permit default values (parental object being null).
 * Since that we have an instance of QCLogger bound to the
 * class that uses it, which means that logger will be deleted
 * as soos as the class does.
 */
class QC_HIDE QCLogger : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(QCLogger)
public:

    explicit QCLogger(const QObject *clazz) :
        QObject(clazz){
        Q_ASSERT(clazz != NULL);

        // setting up
        this->className = clazz->metaObject()->className();
        this->loggerName = "QCLogger::" + this->className;
    }

    void info(const QString &msg){
        return QCLogger::info(this->parent(),msg);
    }

    voida fatal(const QString &msg){
        return QCLogger::fatal(this->parent(),msg);
    }


    static const QCLogger * getQCLogger(const QObject *clazz){
        return new QCLogger(clazz);
    }

    static void info(const QObject *clazz, const QString &msg){
        QDateTime qdt = QDateTime::currentDateTime();
        qDebug() << "[" << qdt.toString("dd.MM.yyyy") << "]"
                 << "[" << qdt.toString("hh:mm:ss") << "]"
                 << "[" << clazz->metaObject()->className() << "]"
                 << " -> " << msg;
    }
    static void fatal(const QObject *clazz, const QString &msg){
        QDateTime qdt = QDateTime::currentDateTime();
        qFatal() << "[" << qdt.toString("dd.MM.yyyy") << "]"
                 << "[" << qdt.toString("hh:mm:ss") << "]"
                 << "[" << clazz->metaObject()->className() << "]"
                 << " -> " << msg;

    }
private:
    QString className;
    QString loggerName;
};
#endif // QUBICORM_H
