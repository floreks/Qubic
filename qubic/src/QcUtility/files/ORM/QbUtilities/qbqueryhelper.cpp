#include "qbqueryhelper.h"

QString QbQueryHelper::getObjectMembers(QString className)
{
    QByteArray byteArray = className.toLocal8Bit();
    int classId = QMetaType::type(byteArray.constData());
    if(classId > 0)
    {
        void *classPtr = QMetaType::create(classId);
        if (classPtr == 0)
        {
            QLOG_ERROR() << "Cannot get " + className + " object members";
            return "*";
        }
        QbPersistable *ptr = (QbPersistable*) classPtr;
        return ptr->getObjectMembers();
    }
    else
    {
        QLOG_ERROR() << "Cannot get " + className + " object members";
        return "*";
    }
}
