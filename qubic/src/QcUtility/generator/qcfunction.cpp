#include "qcfunction.h"

QcFunction::QcFunction() {
    logger = QcLogger::getInstance();
}

QcFunction::QcFunction(QString function) {
    logger = QcLogger::getInstance();
}

void QcFunction::addParameters(std::tuple<QString, QString> parameter) {
    logger->debug("Parameter: " + std::get<0>(parameter));
    parameters[std::get<0>(parameter)] = std::get<1>(parameter);
}

template <typename ... T>
void QcFunction::addParameters(T ... parameter) {
    logger->debug("Test");
    addParameters(parameter...);
}
