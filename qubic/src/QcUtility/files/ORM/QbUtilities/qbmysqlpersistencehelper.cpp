#include "qbmysqlpersistencehelper.h"

int QbMySQLPersistenceHelper::store(QbPersistable& object)
{
    QString gettersPrefix = QbProperties::getInstance()->getProperty("qubic.configuration.getters.prefix");
    QString tableIdentifier = QbProperties::getInstance()->getProperty("qubic.configuration.table.identifier");
    QString ptrGettersSuffix = QbProperties::getInstance()->getProperty("qubic.configuration.pointer.getters.suffix");
    QString objectName = object.getObjectUpperName();
    QString objectID = QString::number(object.getID());
    QString objectString = objectName + ":" + objectID;
    QLOG_DEBUG() << "Reading metadata of object " + objectString;
    if(object.getID() >= 0)
    {
        QLOG_ERROR() << "Object " + objectString + " is already stored, to update it use update method";
        return object.getID();
    }
    QLOG_DEBUG() << "Checking references of object " + objectString;
    QMap<QString, QString> objectMembers;
    QList<QbPersistable*> pointers = object.getPointers();
    QLOG_DEBUG() << QString::number(pointers.size()) + " references to " + objectString + " found";
    for(int i = 0; i < pointers.size(); i++)
    {
        QbPersistable* ptr = pointers.at(i);
        int ptrId = ptr->getID();
        if(ptrId <= 0)
        {
            ptrId = store(*ptr);
        }
        objectMembers[ptr->getObjectUpperName()] = QString::number(ptrId);
    }
    QLOG_INFO() << "Storing object " + objectString;
    for(int i = 0; i < object.metaObject()->methodCount(); i++)
    {
        QMetaMethod method = object.metaObject()->method(i);
        if(method.name().startsWith(gettersPrefix.toStdString().c_str()) && !method.name().endsWith(ptrGettersSuffix.toStdString().c_str()))
        {
            QString memberName = method.name().right(method.name().length() - gettersPrefix.length());
            memberName = memberName.toUpper();
            if(memberName != tableIdentifier.toUpper())
            {
                objectMembers[memberName] = QbMySQLMappingHelper::getStringValue(object, method);
            }
        }
    }
    QLOG_DEBUG() << "Trying to store object " + objectString + " [" + object.getObjectString() + "]";
    QString columns = "(";
    QString values = "(";
    for(auto e : objectMembers.toStdMap()) {
        columns.append(e.first + ", ");
        values.append("'" + e.second + "', ");
    }
    columns = columns.left(columns.length() - 2) + ")";
    values = values.left(values.length() - 2) + ")";
    QString insertStatement = "INSERT INTO " + objectName + " " + columns + " VALUES " + values + ";";
    QLOG_DEBUG() << "SQL statement is ready " + insertStatement;
    if(transactionsEnabled) db.transaction();
    QSqlQuery insertQuery;
    if(insertQuery.exec(insertStatement))
    {
        if(transactionsEnabled) db.commit();
        QLOG_INFO() << "Store operation successfully completed";
        synchronizedObjects << &object;
        return updateObjectIdentifier(object);
    }
    else
    {
        if(transactionsEnabled) db.rollback();
        QLOG_ERROR() << "Store operation failed";
        QLOG_ERROR() << insertQuery.lastError().text();
        return -1;
    }
}

int QbMySQLPersistenceHelper::updateObjectIdentifier(QbPersistable& object)
{
    QString settersPrefix = QbProperties::getInstance()->getProperty("qubic.configuration.setters.prefix");
    QString tableIdentifier = QbProperties::getInstance()->getProperty("qubic.configuration.table.identifier");
    int id = object.getID();
    QString idStatement = "SELECT MAX(" + tableIdentifier + ") FROM " + object.getObjectUpperName() + ";";
    QSqlQuery idQuery;
    if(idQuery.exec(idStatement))
    {
        if(idQuery.next())
        {
            id = idQuery.value(0).toInt();
        }
        QString idSetter = settersPrefix + tableIdentifier.toUpper();
        QMetaObject::invokeMethod(&object, idSetter.toStdString().c_str(), Q_ARG(int, id));
        QLOG_DEBUG() << "Object identifier updated to " + QString::number(id);
    }
    else
    {
        QLOG_ERROR() << "Cannot update object identifier";
        QLOG_ERROR() << idQuery.lastError().text();
    }
    return id;
}

void QbMySQLPersistenceHelper::update(QbPersistable& object)
{
    QString gettersPrefix = QbProperties::getInstance()->getProperty("qubic.configuration.getters.prefix");
    QString tableIdentifier = QbProperties::getInstance()->getProperty("qubic.configuration.table.identifier");
    QString ptrGettersSuffix = QbProperties::getInstance()->getProperty("qubic.configuration.pointer.getters.suffix");
    QString objectName = object.getObjectUpperName();
    QString objectID = QString::number(object.getID());
    QString objectString = objectName + ":" + objectID;
    QLOG_DEBUG() << "Trying to update object " + objectString;
    if(objectID == "-1")
    {
        QLOG_ERROR() << "Update operation failed, object " + objectString + " is not stored yet";
        return;
    }
    QString objectMembers;
    QList<QbPersistable*> pointers = object.getPointers();
    QLOG_DEBUG() << QString::number(pointers.size()) + " references to " + objectString + " found";
    for(int i = 0; i < pointers.size(); i++)
    {
        QbPersistable* ptr = pointers.at(i);
        int ptrId = ptr->getID();
        if(ptrId <= 0)
        {
            ptrId = store(*ptr);
        }
        objectMembers += ptr->getObjectUpperName() + "='" + QString::number(ptrId) + "', ";
    }
    QLOG_INFO() << "Updating object " + objectString;
    for(int i = 0; i < object.metaObject()->methodCount(); i++)
    {
        QMetaMethod method = object.metaObject()->method(i);
        if(method.name().startsWith(gettersPrefix.toStdString().c_str()) && !method.name().endsWith(ptrGettersSuffix.toStdString().c_str()))
        {
            QString memberName = method.name().right(method.name().length() - gettersPrefix.length());
            memberName = memberName.toUpper();
            if(memberName != tableIdentifier.toUpper())
            {
                objectMembers += memberName + "='" + QbMySQLMappingHelper::getStringValue(object, method) + "', ";
            }
        }
    }
    QLOG_DEBUG() << "Trying to update object " + objectString + " [" + object.getObjectString() + "]";
    objectMembers = objectMembers.left(objectMembers.length() - 2);
    QString updateStatement = "UPDATE " + objectName + " SET " + objectMembers + " WHERE ID = " + QString::number(object.getID()) + ";";
    QLOG_DEBUG() << "SQL statement is ready " + updateStatement;
    if(transactionsEnabled) db.transaction();
    QSqlQuery updateQuery;
    if(updateQuery.exec(updateStatement))
    {
        if(transactionsEnabled) db.commit();
        QLOG_INFO() << "Update operation successfully completed";
    }
    else
    {
        if(transactionsEnabled) db.rollback();
        QLOG_ERROR() << "Update operation failed";
        QLOG_ERROR() << updateQuery.lastError().text();
    }
}

void QbMySQLPersistenceHelper::remove(QbPersistable& object)
{
    QString tableIdentifier = QbProperties::getInstance()->getProperty("qubic.configuration.table.identifier");
    QString objectName = object.getObjectUpperName();
    QString objectID = QString::number(object.getID());
    QString objectString = objectName + ":" + objectID;
    QLOG_INFO() << "Trying to remove object " + objectString;
    if(objectID == "-1")
    {
        QLOG_ERROR() << "Remove operation failed, object " + objectString + " is not stored yet";
        return;
    }
    QLOG_DEBUG() << "Trying to remove object " + objectString + " [" + object.getObjectString() + "]";
    QString removeStatement = "DELETE FROM " + objectName + " WHERE " + tableIdentifier.toUpper() + "=" + objectID + ";";
    QLOG_DEBUG() << "SQL statement is ready " + removeStatement;
    if(transactionsEnabled) db.transaction();
    QSqlQuery removeQuery;
    if(removeQuery.exec(removeStatement))
    {
        if(transactionsEnabled) db.commit();
        QLOG_INFO() << "Remove operation successfully completed";
        synchronizedObjects.removeOne(&object);
        removeObjectIdentifier(object);
    }
    else
    {
        if(transactionsEnabled) db.rollback();
        QLOG_ERROR() << "Remove operation failed";
        QLOG_ERROR() << removeQuery.lastError().text();
    }
}

void QbMySQLPersistenceHelper::removeObjectIdentifier(QbPersistable& object)
{
    QString settersPrefix = QbProperties::getInstance()->getProperty("qubic.configuration.setters.prefix");
    QString tableIdentifier = QbProperties::getInstance()->getProperty("qubic.configuration.table.identifier");
    int id = -1;
    QString idSetter = settersPrefix + tableIdentifier.toUpper();
    QMetaObject::invokeMethod(&object, idSetter.toStdString().c_str(), Q_ARG(int, id));
    QLOG_DEBUG() << "Object identifier updated to " + QString::number(id);
}

QList<QbPersistable*> QbMySQLPersistenceHelper::load(QbPersistable& object, int id)
{
    QString settersPrefix = QbProperties::getInstance()->getProperty("qubic.configuration.setters.prefix");
    QString tableIdentifier = QbProperties::getInstance()->getProperty("qubic.configuration.table.identifier");
    QString ptrGettersSuffix = QbProperties::getInstance()->getProperty("qubic.configuration.pointer.getters.suffix");
    QString objectName = object.getObjectUpperName();
    if(id < 0)
    {
        QLOG_INFO() << "Trying to load objects " + objectName;
    }
    else
    {
        QLOG_INFO() << "Trying to load objects " + objectName + " with identifier " + QString::number(id);
    }
    QList<QbPersistable*> result = QList<QbPersistable*>();
    QString selectStatement = "SELECT ";
    QMap<QString, QString> objectMembers;
    for(int i = 0; i < object.metaObject()->methodCount(); i++)
    {
        QMetaMethod method = object.metaObject()->method(i);
        if(method.name().startsWith(settersPrefix.toStdString().c_str()))
        {
            QString memberName = method.name().right(method.name().length() - settersPrefix.length());
            if(memberName.endsWith(ptrGettersSuffix.toStdString().c_str())) memberName = memberName.left(memberName.size() - ptrGettersSuffix.size());
            memberName = memberName.toUpper();
            objectMembers[memberName] = "";
            selectStatement.append(memberName + ", ");
        }
    }
    QLOG_DEBUG() << "Trying to load objects " + objectName + " from database";
    selectStatement = selectStatement.left(selectStatement.length() - 2) + " FROM " + objectName;
    if(id < 0)
    {
        selectStatement += ";";
    }
    else
    {
        selectStatement += " WHERE " + tableIdentifier.toUpper() + "=" + QString::number(id);
        selectStatement += ";";
    }
    QLOG_DEBUG() << "SQL statement is ready " + selectStatement;
    QSqlQuery selectQuery;
    if(selectQuery.exec(selectStatement))
    {
        QString className = object.metaObject()->className();
        QByteArray byteArray = className.toLocal8Bit();
        int classId = QMetaType::type(byteArray.constData());
        if(classId > 0)
        {
            while(selectQuery.next())
            {
                void *classPtr = QMetaType::create(classId);
                if (classPtr == 0)
                {
                    QLOG_ERROR() << "Load operation failed, cannot initialize " + className + " object";
                    return result;
                }
                QbPersistable *ptr = (QbPersistable*) classPtr;
                for(int i = 0; i < ptr->metaObject()->methodCount(); i++)
                {
                    QMetaMethod method = ptr->metaObject()->method(i);
                    if(method.name().startsWith(settersPrefix.toStdString().c_str()))
                    {
                        if(!method.name().endsWith(ptrGettersSuffix.toStdString().c_str()))
                        {
                            QString memberName = method.name().right(method.name().length() - settersPrefix.length());
                            memberName = memberName.toUpper();
                            QString memberValue = selectQuery.value(memberName).toString();
                            QbMySQLMappingHelper::setStringValue(ptr, method, memberValue);
                        }
                        else
                        {
                            QString ptrName = QString(method.name());
                            ptrName = ptrName.left(ptrName.size() - ptrGettersSuffix.size());
                            ptrName = ptrName.right(ptrName.size() - settersPrefix.size());
                            QLOG_TRACE() << "Loading " + ptrName + " reference";
                            QString ptrValue = selectQuery.value(ptrName).toString();
                            int typeIdForPtr = QMetaType::type(ptrName.toStdString().c_str());
                            void *classPtrForPtr = QMetaType::create(typeIdForPtr);
                            if (classPtrForPtr == 0)
                            {
                                QLOG_ERROR() << "Load operation failed, cannot initialize " + ptrName + " object";
                                return result;
                            }
                            QbPersistable *ptrForPtr = (QbPersistable*) classPtrForPtr;
                            QList<QbPersistable*> pointer = load(*ptrForPtr, ptrValue.toInt());
                            if(pointer.size() != 1)
                            {
                                QLOG_ERROR() << "Did not found " + ptrName + " with identifier " + ptrValue;
                                return result;
                            }
                            QMetaObject::invokeMethod(ptr, method.name(), Q_ARG(QbPersistable*, pointer.at(0)));
                        }
                    }
                }
                result.append(ptr);
            }
            QLOG_DEBUG() << "Load operation successfully completed";
            return result;
        }
        else
        {
            QLOG_ERROR() << "Load operation failed, class " + className + " is not registered as Qt meta type";
            return result;
        }
    }
    else
    {
        QLOG_ERROR() << "Load operation failed";
        QLOG_ERROR() << selectQuery.lastError().text();
        return result;
    }
}

QList<QbPersistable*> QbMySQLPersistenceHelper::load(QbQuery* query)
{
    QString settersPrefix = QbProperties::getInstance()->getProperty("qubic.configuration.setters.prefix");
    QString ptrGettersSuffix = QbProperties::getInstance()->getProperty("qubic.configuration.pointer.getters.suffix");
     QLOG_DEBUG() << "Trying to query objects " + query->getClassName().toUpper() + " from database";
     QList<QbPersistable*> result = QList<QbPersistable*>();
     QLOG_DEBUG() << "SQL statement is ready " + query->getQuery();
     QSqlQuery selectQuery;
     if(selectQuery.exec(query->getQuery()))
     {
         QByteArray byteArray = query->getClassName().toLocal8Bit();
         int classId = QMetaType::type(byteArray.constData());
         if(classId > 0)
         {
             while(selectQuery.next())
             {
                 void *classPtr = QMetaType::create(classId);
                 if (classPtr == 0)
                 {
                     QLOG_ERROR() << "Load operation failed, cannot initialize " + query->getClassName() + " object";
                     return result;
                 }
                 QbPersistable *ptr = (QbPersistable*) classPtr;
                 for(int i = 0; i < ptr->metaObject()->methodCount(); i++)
                 {
                     QMetaMethod method = ptr->metaObject()->method(i);
                     if(method.name().startsWith(settersPrefix.toStdString().c_str()))
                     {
                         if(!method.name().endsWith(ptrGettersSuffix.toStdString().c_str()))
                         {
                             QString memberName = method.name().right(method.name().length() - settersPrefix.length());
                             memberName = memberName.toUpper();
                             QString memberValue = selectQuery.value(memberName).toString();
                             QbMySQLMappingHelper::setStringValue(ptr, method, memberValue);
                         }
                         else
                         {
                             QString ptrName = QString(method.name());
                             ptrName = ptrName.left(ptrName.size() - ptrGettersSuffix.size());
                             ptrName = ptrName.right(ptrName.size() - settersPrefix.size());
                             QLOG_TRACE() << "Loading " + ptrName + " reference";
                             QString ptrValue = selectQuery.value(ptrName).toString();
                             int typeIdForPtr = QMetaType::type(ptrName.toStdString().c_str());
                             void *classPtrForPtr = QMetaType::create(typeIdForPtr);
                             if (classPtrForPtr == 0)
                             {
                                 QLOG_ERROR() << "Load operation failed, cannot initialize " + ptrName + " object";
                                 return result;
                             }
                             QbPersistable *ptrForPtr = (QbPersistable*) classPtrForPtr;
                             QList<QbPersistable*> pointer = load(*ptrForPtr, ptrValue.toInt());
                             if(pointer.size() != 1)
                             {
                                 QLOG_ERROR() << "Did not found " + ptrName + " with identifier " + ptrValue;
                                 return result;
                             }
                             QMetaObject::invokeMethod(ptr, method.name(), Q_ARG(QbPersistable*, pointer.at(0)));
                         }
                     }
                 }
                 result.append(ptr);
             }
             QLOG_DEBUG() << "Load operation successfully completed";
             return result;
         }
         else
         {
             QLOG_ERROR() << "Load operation failed, class " + query->getClassName() + " is not registered as Qt meta type";
             return result;
         }
     }
     else
     {
         QLOG_ERROR() << "Load operation failed";
         QLOG_ERROR() << selectQuery.lastError().text();
         return result;
     }

}
