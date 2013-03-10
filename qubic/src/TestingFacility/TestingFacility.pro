#-------------------------------------------------
#
# Project created by QtCreator 2012-12-23T23:41:02
#
#-------------------------------------------------

QT       += core testlib sql
QT       -= gui

TARGET          = TestingFacility
CONFIG          += console
CONFIG          -= app_bundle
QMAKE_CXXFLAGS  += -std=c++0x

TEMPLATE = app

SOURCES +=

HEADERS += \
    ConnectionManagerTestUnit.h


unix:!macx: LIBS += -L$$OUT_PWD/../QubicORM/ -lQubicORM

INCLUDEPATH += $$PWD/../QubicORM
DEPENDPATH += $$PWD/../QubicORM
