#include "qslogdestbox.h"

QsLogging::QsLogDestBox::QsLogDestBox(QTextBrowser *box) {
    this->box = box;
}

void QsLogging::QsLogDestBox::write(const QString &message, Level) {
    box->append(message);
    box->update();
}

bool QsLogging::QsLogDestBox::isValid() {
    return true;
}
