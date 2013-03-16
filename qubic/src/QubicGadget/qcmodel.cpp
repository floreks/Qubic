#include "qcmodel.h"

QcMetaModel QcModel::getMetaModel() const{
    return QcModel::metaModel;
}

QcModel::QcModel(const QMetaObject *meta, QObject *parent) :
    QObject(parent){
    this->metaModel = QcMetaModel::registerInternalModel(meta);
}

QcModel::~QcModel(){
}

void QcModel::saveModel(){
    //marmac functionality should go here
}

void QcModel::loadModel(){
    //marmac functionality should go here
}

void QcModel::deleteModel(){
    //marmac functionality should go here
}

QString QcModel::toString() const{
    return "";
}

bool QcModel::equals(QcModel *const model){
    Q_UNUSED(model)
    return false;
}
