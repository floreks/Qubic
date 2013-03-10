#include "qcconnectionmanager.h"

class DataHolder {
    QString user,
            password,
            host,
            database;
    qint32  port;
};

class QCConnectionManagerData : public QSharedData {
public:
    QCConnectionManagerData() :
        data(new DataHolder){
    }

    DataHolder *data;
    QSqlDatabase db;
};

QCConnectionManager::QCConnectionManager(QObject *parent) :
    QObject(parent),
    data(new QCConnectionManagerData()){
    QCLogger::info(this,"All done");
}

QCConnectionManager::QCConnectionManager(const QCConnectionManager &rhs, QObject *parent) :
    QObject(parent),
    data(rhs.data){
}

QCConnectionManager &QCConnectionManager::operator=(const QCConnectionManager &rhs){
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

QCConnectionManager::~QCConnectionManager(){
}
