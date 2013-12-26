#-------------------------------------------------
#
# Project created by QtCreator 2013-09-12T00:43:58
#
#-------------------------------------------------

QT       += core widgets sql

QT       -= gui

TARGET = TestingFacility
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += c++11

TEMPLATE = app


SOURCES += main.cpp

INCLUDEPATH += $$PWD/../QcCore \
               $$PWD/../QcUtility

ParentDirectory = $$PWD\..\..

RCC_DIR = "$$ParentDirectory\build\RCCFiles"
UI_DIR = "$$ParentDirectory\build\UICFiles"
MOC_DIR = "$$ParentDirectory\build\MOCFiles"
OBJECTS_DIR = "$$ParentDirectory\build\ObjFiles"

CONFIG(debug, debug|release) {
    DESTDIR = "$$ParentDirectory\out"
    TARGET = QcCored
    LIBS += -L$$PWD\..\..\include \
        -lQcCored -lQcUtilityd
} else {
    DESTDIR = "$$ParentDirectory\out"
    TARGET = QcCore
    LIBS += -L$$PWD\..\..\include \
        -lQcCore -lQcUtility
}
