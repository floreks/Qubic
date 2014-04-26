#ifndef QCSOURCEFILE_H
#define QCSOURCEFILE_H

#include "qcheaderfile.h"

class QcSourceFile : public QcHeaderFile
{
private:
    QString getPublicSection();
public:
    using QcHeaderFile::QcHeaderFile;

    friend QTextStream& operator<<(QTextStream &str, QcSourceFile &file);
};

#endif // QCSOURCEFILE_H
