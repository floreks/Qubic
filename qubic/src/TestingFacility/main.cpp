#include "qcobject.h"
#include "qcpersistable.h"
#include "qclogger.h"

#include <iostream>
#include <QMetaMethod>

using namespace std;

int main()
{
    QcLogger::setLoggingLevel(QsLogging::DebugLevel);
    QcPersistable pers;
    QcPersistable x;
    QList<QMetaMethod> methods;
    QString retVal;
    for(int i=0;i<x.metaObject()->methodCount();i++) {
        methods.push_back(x.metaObject()->method(i));
        if(methods.at(i).methodSignature().contains("get"))
            methods.at(i).invoke(&x,Q_RETURN_ARG(QString,retVal));
    }

    qDebug() << retVal;

    return 0;
}
