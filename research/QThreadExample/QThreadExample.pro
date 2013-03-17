#-------------------------------------------------
#
# Project created by QtCreator 2013-03-16T18:52:01
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QThreadExample
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ctimer.cpp \
    cupdater.cpp

HEADERS  += mainwindow.h \
    ctimer.h \
    cupdater.h

FORMS    += mainwindow.ui
