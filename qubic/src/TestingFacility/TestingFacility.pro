#-------------------------------------------------
#
# Project created by QtCreator 2013-09-12T00:43:58
#
#-------------------------------------------------

QT       += core widgets

QT       -= gui

TARGET = TestingFacility
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += c++11

TEMPLATE = app


SOURCES += main.cpp

INCLUDEPATH += $$PWD/../QcCore \
               $$PWD/../QcUtility
LIBS += -L$$PWD\..\..\build\debug\QcCore\debug \
        -L$$PWD\..\..\build\debug\QcUtility\debug \
    -lQcCore -lQcUtility
