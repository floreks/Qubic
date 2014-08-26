#include "qbmappinghelper.h"

QString QbMappingHelper::getStringValue(QbPersistable &object, QMetaMethod method)
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
