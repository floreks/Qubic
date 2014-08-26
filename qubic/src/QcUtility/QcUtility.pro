#-------------------------------------------------
#
# Project created by QtCreator 2013-09-09T22:27:48
#
#-------------------------------------------------

QT       -= gui
QT       += xml xmlpatterns sql widgets

TEMPLATE = lib
CONFIG += c++11

DEFINES += QCUTILITY_LIBRARY

SOURCES += \
    qclogger.cpp


HEADERS +=\
    qcutility_global.h \
    qclogger.h


TRANSLATIONS = qubic_pl_PL.ts

include(QsLog\QsLog.pri)
include(database\database.pri)
include(generator\generator.pri)
include(properties\properties.pri)
include(schema\schema.pri)

PWD = $$PWD/..
OUT_PWD = $$PWD/..

RCC_DIR = "$$OUT_PWD/build/RCCFiles"
UI_DIR = "$$OUT_PWD/build/UICFiles"
MOC_DIR = "$$OUT_PWD/build/MOCFiles"
OBJECTS_DIR = "$$OUT_PWD/build/ObjFiles"
QMAKE_LIBDIR_QT = $$QMAKESPEC/../../bin
DESTDIR = "$$OUT_PWD/include"

CONFIG(debug, debug|release) {
    TARGET = QcUtilityd
}
CONFIG(release, debug|release) {
    TARGET = QcUtility
}

RESOURCES += \
    qresource.qrc

