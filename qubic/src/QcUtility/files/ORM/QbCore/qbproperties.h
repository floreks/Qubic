#ifndef QBPROPERTIES_H
#define QBPROPERTIES_H

#include <QMap>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QDir>
#include <QTextStream>
#include <../QsLog/QsLog.h>

class QbProperties
{
public:
    static QbProperties* getInstance();
    QString getProperty(QString property);
    void setProperty(QString property, QString value);
    void store();

private:
    QbProperties();
    static QbProperties* instance;
    QMap<QString,QString> properties;
    static QString path;
};

#endif // QBPROPERTIES_H
