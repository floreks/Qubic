#ifndef QCMETATABLE_H
#define QCMETATABLE_H

#include <QList>
#include <QString>
#include <QDebug>

#include "qcmetafield.h"

enum RelationType {
    OneToMany = 1,
    ManyToMany = 2,
    None = 3
};

class QcMetaTable
{
private:
    QString tableName;
    QList<QcMetaField*> fields;
    RelationType relationType = RelationType::None;
    QcMetaTable* jointTable;
    QcMetaTable* relatedTable;
public:
    explicit QcMetaTable(QString tableName);
    void addField(QcMetaField *field);
    void setFields(QList<QcMetaField*> fields);
    void setJointTable(QcMetaTable *table);
    void setRelatedTable(QcMetaTable *table);
    void setRelationType(RelationType type);

    QString getName()const;
    QList<QcMetaField*> getFields()const;
    QcMetaTable* getJointTable()const;
    QcMetaTable* getRelatedTable()const;
    RelationType getRelationType()const;

    bool operator<(const QcMetaTable &obj)const;
    friend QDebug operator<<(QDebug os, const QcMetaTable &t);

};

#endif // QCMETATABLE_H
