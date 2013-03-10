#include "qubeinterface.h"

QC_BEGIN_NAMESPACE

QubeInterface::QubeInterface(QObject *parent) :
    QObject(parent){
}

bool QubeInterface::exists(const QString &field, const QVariant &query){
    return this->filter(QPair<QString,QVariant>(field,query)).size() > 0;
}

QC_END_NAMESPACE
