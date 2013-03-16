#-------------------------------------------------
#
# Project created by QtCreator 2013-03-16T11:57:36
#
#-------------------------------------------------

QT       -= gui
QT       += core

CONFIG   += c++11
QMAKE_CXXFLAGS += -std=c++0x

TARGET = QubicGadget
TEMPLATE = lib

DEFINES += QUBICGADGET_LIBRARY

SOURCES += \
    qcmodel.cpp \
    qcmetamodel.cpp \
    qcmetafield.cpp \
    qccolumn.cpp

HEADERS +=\
    qcmodel.h \
    qcmetamodel.h \
    qcmetafield.h \
    qccolumn.h \
    comparision/qcequalable.h \
    comparision/qccomparision.h \
    comparision/qccomparator.h \
    comparision/qccomparable.h \
    interfaces/qcpersistable.h \
    interfaces/qcdescribable.h \
    qubicgadgetdefs.h \
    exception/qcerrorcode.h
