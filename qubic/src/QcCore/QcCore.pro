#-------------------------------------------------
#
# Project created by QtCreator 2013-09-09T22:26:23
#
#-------------------------------------------------

QT       -= gui

TARGET = QcCore
TEMPLATE = lib
CONFIG += c++11

DEFINES += QCCORE_LIBRARY

SOURCES += \
    qcobject.cpp \
    qcpersistable.cpp

HEADERS +=\
        qccore_global.h \
    qcobject.h \
    qcpersistable.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

INCLUDEPATH += $$PWD/../QcUtility

LIBS += -LG:\Projects\Qubic\qubic\build\debug\QcUtility\debug \
    -lQcUtility
