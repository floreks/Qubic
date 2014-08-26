#include "qbpersistable.h"
#include "../QbUtilities/qbmappinghelper.h"

QString QbPersistable::getObjectUpperName() {
    QString objectName = this->metaObject()->className();
    return objectName.toUpper();
}

QString QbPersistable::getObjectString() {
    QString prefix = QbProperties::getInstance()->getProperty("qubic.configuration.getters.prefix");
    QString objectString;
    for(int i = 0; i < this->metaObject()->methodCount(); i++)
    {
        QMetaMethod method = this->metaObject()->method(i);
        if(method.name().startsWith(prefix.toStdString().c_str()))
        {
            QString memberName = method.name().right(method.name().length() - prefix.length());
            memberName = memberName.toUpper();
            QString memberValue = QbMappingHelper::getStringValue(*this, method);
            objectString.append(memberName + " = " + memberValue + "; ");
        }
    }
    objectString = objectString.left(objectString.length() - 2);
    return objectString;
}

QString QbPersistable::getObjectMembers()
{
    QString prefix = QbProperties::getInstance()->getProperty("qubic.configuration.getters.prefix");
    QString suffix = QbProperties::getInstance()->getProperty("qubic.configuration.pointer.getters.suffix");
    QString tableIdentifier = QbProperties::getInstance()->getProperty("qubic.configuration.table.identifier");
    QString objectMembers = "";
    for(int i = 0; i < this->metaObject()->methodCount(); i++)
    {
        QMetaMethod method = this->metaObject()->method(i);
        if(method.name().startsWith(prefix.toStdString().c_str()))
        {
            QString memberName = method.name().right(method.name().length() - prefix.length());
            if(memberName.endsWith(suffix.toStdString().c_str()))
            {
                memberName = memberName.left(memberName.length() - suffix.length());
            }
            objectMembers += memberName.toUpper() + ", ";
        }
    }
    objectMembers += tableIdentifier.toUpper();
    return objectMembers;
}
