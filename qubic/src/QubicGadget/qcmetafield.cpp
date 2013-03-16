#include "qcmetafield.h"
#include "qccolumn.h"
#include <QSharedData>

/**
 * @brief The QcMetaFieldData class
 */
class QcMetaFieldData : public QSharedData {
public:
    QcColumn column;
    QMetaProperty metaProperty;
};

QcMetaField::QcMetaField() : data(new QcMetaFieldData){
}

QcMetaField::QcMetaField(const QcMetaField &rhs) : data(rhs.data){
}

QcMetaField &QcMetaField::operator=(const QcMetaField &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

QcMetaField::~QcMetaField(){
}

void QcMetaField::setColumn(const QcColumn &column){
    this->data.data()->column = column;
}

QcColumn QcMetaField::getColumn() const{
    return this->data.data()->column;
}

void QcMetaField::setMetaProperty(const QMetaProperty &property){
    this->data.data()->metaProperty = property;
}

QMetaProperty QcMetaField::getMetaProperty() const{
    return this->data.data()->metaProperty;
}
