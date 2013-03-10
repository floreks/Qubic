#-------------------------------------------------
#
# Project created by QtCreator 2012-12-24T02:40:56
#
#-------------------------------------------------

QT       += sql xml xmlpatterns
QT       -= gui

#so at to let project be compiled with C++ 11 at the back
    QMAKE_CXXFLAGS  += -std=c++0x
#so at to let project be compiled with C++ 11 at the back

 # Use Precompiled headers (PCH)
CONFIG   += precompile_header
PRECOMPILED_HEADER  = private/pch.h

TARGET   = QubicORM
TEMPLATE = lib

DEFINES += QUBICORM_LIBRARY

SOURCES += \
    ConnectionModule/qcconnectionmanager.cpp \
    QubeModule/qubeprocessor.cpp \
    ConfigurationModule/qcconfigurationreader.cpp \
    QubiconsModule/qubiconcompiler.cpp \
    QubeModule/model/qubemodel.cpp \
    QubeModule/model/qubeinterface.cpp

HEADERS += private/qubicorm.h\
    ConnectionModule/qcconnectionmanager.h \
    private/pch.h \
    QCSession \
    QubeModule/qubeprocessor.h \
    ConfigurationModule/qcconfigurationreader.h \
    QubiconsModule/qubicons.h \
    QubiconsModule/qubicon.h \
    QubiconsModule/qubiconcompiler.h \
    QubeModule/model/qubemodel.h \
    QubeModule/model/qubeinterface.h

OTHER_FILES += \
    README.md \
    ConnectionModule/README.md \
    ConfigurationModule/README.md
