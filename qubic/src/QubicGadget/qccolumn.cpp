#include "qccolumn.h"
#include <QSharedData>

class QcColumnData : public QSharedData {
public:
    QString name;
    QcColumn::ColumnOptions options;
    qint16 length;
    QVariant defaultValue;
};

QcColumn::QcColumn() :
    data(new QcColumnData){
}

QcColumn::QcColumn(const QcColumn &rhs) :
    data(rhs.data){
}

QcColumn &QcColumn::operator=(const QcColumn &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

QcColumn::~QcColumn(){
}

void QcColumn::setName(const QString &name){
    this->data.data()->name = name;
}

QString QcColumn::getName() const{
    return this->data.data()->name;
}

void QcColumn::setOptions(QcColumn::ColumnOptions options){
    this->data.data()->options = options;
}

QcColumn::ColumnOptions QcColumn::getOptions() const{
    return this->data.data()->options;
}

void QcColumn::setMaxLength(qint16 length){
    this->data.data()->length = length;
}

qint16 QcColumn::getMaxLength() const{
    return this->data.data()->length;
}

void QcColumn::setDefaultValue(const QVariant &val){
    this->data.data()->defaultValue = val;
}

QVariant QcColumn::getDefaultValue() const{
    return this->data.data()->defaultValue;
}

