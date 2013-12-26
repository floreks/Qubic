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

INCLUDEPATH += $$PWD/../QcUtility

ParentDirectory = $$PWD\..\..

RCC_DIR = "$$ParentDirectory\build\RCCFiles"
UI_DIR = "$$ParentDirectory\build\UICFiles"
MOC_DIR = "$$ParentDirectory\build\MOCFiles"
OBJECTS_DIR = "$$ParentDirectory\build\ObjFiles"

CONFIG(debug, debug|release) {
    DESTDIR = "$$ParentDirectory\include"
    TARGET = QcCored
    LIBS += -L$$PWD\..\..\include \
        -lQcUtilityd
} else {
    DESTDIR = "$$ParentDirectory\include"
    TARGET = QcCore
    LIBS += -L$$PWD\..\..\include \
        -lQcUtility
}
