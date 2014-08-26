#ifndef QCPROJECTFILE_H
#define QCPROJECTFILE_H

#include <QList>
#include <QString>

#include <QTextStream>

class QcProjectFile
{
private:
    QList<QString> headers;
    QList<QString> sources;
public:
    QcProjectFile();

    void addHeader(QString headerName);
    void addSource(QString sourceName);

    friend QTextStream& operator<<(QTextStream &str, QcProjectFile &file);
};

#endif // QCPROJECTFILE_H
