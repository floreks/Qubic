#-------------------------------------------------
#
# Utilities are helpful tools that were recognized
# by reusable in some area and put into this part of
# Qubic project.
# All sort of custom string, text files processing
# can be found here
#
#-------------------------------------------------

QT       += sql xml xmlpatterns

QT       -= gui

TARGET = Utilities
TEMPLATE = lib

DEFINES += UTILITIES_LIBRARY

SOURCES += utilities.cpp

HEADERS += utilities.h\
        Utilities_global.h
