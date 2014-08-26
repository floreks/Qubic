#include "qbproperties.h"

QbProperties* QbProperties::instance = NULL;
QString QbProperties::path = QDir::currentPath() + "/qb.properties";

QbProperties::QbProperties()
{
    QFile file(path);
    if(!file.exists() || !file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QLOG_FATAL() << "Cannot open properties file " + path;
        return;
    }
    QTextStream in(&file);
    while(!in.atEnd())
    {
        QString line = in.readLine();
        QStringList fields = line.split("=");
        if(line.at(0)!='#' && fields.size()==2) {
            properties.insert(properties.end(), fields.at(0), fields.at(1));
        }
    }
    file.close();
    QLOG_INFO() << "Properties successfully read from " + path;
}

QbProperties* QbProperties::getInstance()
{
    if (instance == NULL) instance = new QbProperties();
    return instance;
}

QString QbProperties::getProperty(QString property)
{
    if(!properties.contains(property))
    {
        QLOG_ERROR() << "Cannot read property " + property;
    }
    return properties.value(property);
}

void QbProperties::setProperty(QString property, QString value)
{
    properties.insert(property,value);
}

void QbProperties::store()
{
    QFile file(path);
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QLOG_FATAL() << "Cannot open properties file " + path;
        return;
    }
    QTextStream out(&file);
    out << "#############################################" << endl
        << "#                                           #" << endl
        << "#   Qubic properties file                   #" << endl
        << "#                                           #" << endl
        << "#   To comment line use # character         #" << endl
        << "#   Do not leave any spaces                 #" << endl
        << "#                                           #" << endl
        << "#############################################" << endl << endl;
    for(auto prop : properties.keys())
    {
        out << prop << "=" << properties.value(prop) << endl;
    }
    file.close();
}
