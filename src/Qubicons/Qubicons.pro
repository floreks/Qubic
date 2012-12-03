#-------------------------------------------------
#
# Qubicons is set of all reuasable macros defined thanks
# Qt meta system.
# Qubicons are ment to be used to describe classes that
# are used as models of tables from DBMS.
#
#-------------------------------------------------

QT       -= gui

TARGET = Qubicons
TEMPLATE = lib

DEFINES += QUBICONS_LIBRARY

SOURCES += qubicons.cpp

HEADERS += qubicons.h\
        Qubicons_global.h
