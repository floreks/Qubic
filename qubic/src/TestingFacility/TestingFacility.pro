#-------------------------------------------------
#
# Project created by QtCreator 2013-09-12T00:43:58
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = TestingFacility
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += c++11

TEMPLATE = app


SOURCES += main.cpp

INCLUDEPATH += $$PWD/../QcCore \
               $$PWD/../QcUtility
LIBS += -LG:\Projects\Qubic\qubic\build\debug\QcCore\debug \
        -LG:\Projects\Qubic\qubic\build\debug\QcUtility\debug \
    -lQcCore -lQcUtility
