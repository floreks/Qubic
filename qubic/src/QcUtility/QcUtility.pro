#-------------------------------------------------
#
# Project created by QtCreator 2013-09-09T22:27:48
#
#-------------------------------------------------

QT       -= gui
QT       += xml xmlpatterns

TARGET = QcUtility
TEMPLATE = lib
CONFIG += c++11

DEFINES += QCUTILITY_LIBRARY

SOURCES += \
    qclogger.cpp \
    qcdatabase.cpp \
    qcpropertiesmanager.cpp

HEADERS +=\
    qcutility_global.h \
    qclogger.h \
    qcdatabase.h \
    qcpropertiesmanager.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

include(QsLog\QsLog.pri)
