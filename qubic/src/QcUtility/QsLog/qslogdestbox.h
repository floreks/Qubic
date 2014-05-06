#ifndef QSLOGDESTBOX_H
#define QSLOGDESTBOX_H

#include "QsLogDest.h"

#include <QTextBrowser>

namespace QsLogging
{

class QsLogDestBox : public Destination
{
public:
    QsLogDestBox(QTextBrowser *box);
    virtual void write(const QString& message, Level level);
    virtual bool isValid();
private:
    QTextBrowser *box;
};

}

#endif // QSLOGDESTBOX_H
