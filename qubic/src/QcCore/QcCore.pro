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

TRANSLATIONS += qubic_pl_PL.ts

INCLUDEPATH += $$PWD/../QcUtility

PWD = $$PWD/..
OUT_PWD = $$PWD/..

RCC_DIR = "$$OUT_PWD/build/RCCFiles"
UI_DIR = "$$OUT_PWD/build/UICFiles"
MOC_DIR = "$$OUT_PWD/build/MOCFiles"
OBJECTS_DIR = "$$OUT_PWD/build/ObjFiles"
QMAKE_LIBDIR_QT = $$QMAKESPEC/../../bin
DESTDIR = "$$OUT_PWD/include"

CONFIG(debug, debug|release) {
    TARGET = QcCored
    LIBS += -L$$PWD/../include \
        -lQcUtilityd
}
CONFIG(release, debug|release) {
    TARGET = QcCore
    LIBS += -L$$PWD/../include \
        -lQcUtility
}
