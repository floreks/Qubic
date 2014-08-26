#include "qbmysqlmappinghelper.h"

QString QbMySQLMappingHelper::getStringValue(QbPersistable &object, QMetaMethod method)
{
    QString returnValue = "";
    QString typeName = method.typeName();
    if(!typeName.compare("int", Qt::CaseInsensitive)) {
        int memberValue;
        QMetaObject::invokeMethod(&object, method.name(), Q_RETURN_ARG(int, memberValue));
        returnValue = QString::number(memberValue);
    }
    else if(!typeName.compare("QString", Qt::CaseInsensitive))
    {
        QMetaObject::invokeMethod(&object, method.name(), Q_RETURN_ARG(QString, returnValue));
    }
    else if(!typeName.compare("QDate", Qt::CaseInsensitive))
    {
        QDate memberValue;
        QMetaObject::invokeMethod(&object, method.name(), Q_RETURN_ARG(QDate, memberValue));
        returnValue = memberValue.toString("yyyy-MM-dd");
    }
    else if(!typeName.compare("QDateTime", Qt::CaseInsensitive))
    {
        QDateTime memberValue;
        QMetaObject::invokeMethod(&object, method.name(), Q_RETURN_ARG(QDateTime, memberValue));
        returnValue = memberValue.toString("yyyy-MM-dd hh:mm:ss");
    }
    else if(!typeName.compare("double", Qt::CaseInsensitive))
    {
        double memberValue;
        QMetaObject::invokeMethod(&object, method.name(), Q_RETURN_ARG(double, memberValue));
        returnValue = QString::number(memberValue);
    }
    return returnValue;
}

void QbMySQLMappingHelper::setStringValue(QbPersistable *object, QMetaMethod method, QString value)
{
    if(method.parameterCount() < 1)
    {
        QLOG_FATAL() << "Setter " + method.name() + " has wrong number of parameters";
        QLOG_DEBUG() << "Setter " + method.name() + " has " + QString::number(method.parameterCount()) + " parameters instead of 1";
        return;
    }
    int typeId = method.parameterType(0);
    QString typeName = QMetaType::typeName(typeId);
    if(!typeName.compare("int", Qt::CaseInsensitive)) {
        QMetaObject::invokeMethod(object, method.name(), Q_ARG(int, value.toInt()));
    }
    else if(!typeName.compare("QString", Qt::CaseInsensitive))
    {
        QMetaObject::invokeMethod(object, method.name(), Q_ARG(QString, value));
    }
    else if(!typeName.compare("QDate", Qt::CaseInsensitive))
    {
        QDate date = QDate::fromString(value, "yyyy-MM-dd");
        QMetaObject::invokeMethod(object, method.name(), Q_ARG(QDate, date));
    }
    else if(!typeName.compare("QDateTime", Qt::CaseInsensitive))
    {
        QDateTime dateTime = QDateTime::fromString(value, "yyyy-MM-ddThh:mm:ss");
        QMetaObject::invokeMethod(object, method.name(), Q_ARG(QDateTime, dateTime));
    }
    else if(!typeName.compare("double", Qt::CaseInsensitive))
    {
        QMetaObject::invokeMethod(object, method.name(), Q_ARG(double, value.toDouble()));
    }
}
