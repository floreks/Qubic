#-------------------------------------------------
#
# Project created by QtCreator 2013-09-09T22:27:48
#
#-------------------------------------------------

QT       -= gui
QT       += xml xmlpatterns

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

include(QsLog\QsLog.pri)

ParentDirectory = $$PWD\..\..

RCC_DIR = "$$ParentDirectory\build\RCCFiles"
UI_DIR = "$$ParentDirectory\build\UICFiles"
MOC_DIR = "$$ParentDirectory\build\MOCFiles"
OBJECTS_DIR = "$$ParentDirectory\build\ObjFiles"

CONFIG(debug, debug|release) {
    DESTDIR = "$$ParentDirectory\include"
    TARGET = QcUtilityd
} else {
    DESTDIR = "$$ParentDirectory\include"
    TARGET = QcUtility
}
