#include "qcschema.h"

using std::list;
using std::map;
using std::iterator;

QcSchema::QcSchema() {
}

void QcSchema::addTable(QcMetaTable table) {
    schema[table] = QList<QcMetaTable>();
}

void QcSchema::setChildren(QcMetaTable parent, QList<QcMetaTable> children) {
    QMap<QcMetaTable,QList<QcMetaTable>>::iterator it = schema.find(parent);

    if(it != schema.end()) {
        it.value() = children;
    } else {
        schema[parent] = children;
    }
}

void QcSchema::addChild(QcMetaTable parent, QcMetaTable child) {
    QMap<QcMetaTable,QList<QcMetaTable>>::iterator it = schema.find(parent);

    if(it != schema.end()) {
        it.value().push_back(child);
    } else {
        schema[parent].push_back(child);
    }
}

QcMetaTable QcSchema::getTable(QString tableName) {
    QcMetaTable toCompare(tableName);
    QMap<QcMetaTable,QList<QcMetaTable>>::iterator it = schema.find(toCompare);

    if(it != schema.end()) {
        return it.key();
    }

    return QcMetaTable("");
}

QList<QcMetaTable> QcSchema::getChildrenOf(QString tableName) {
    QList<QcMetaTable> result;
    QcMetaTable toCompare(tableName);
    QMap<QcMetaTable,QList<QcMetaTable>>::iterator it = schema.find(toCompare);

    if(it != schema.end()) {
        result = it.value();
    }

    return result;
}
