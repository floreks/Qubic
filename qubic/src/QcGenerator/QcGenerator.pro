#-------------------------------------------------
#
# Project created by QtCreator 2014-05-06T21:29:09
#
#-------------------------------------------------

QT       += core gui xml xmlpatterns sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = QcGenerator
TEMPLATE = app


SOURCES += main.cpp\
        qcgenerator.cpp

HEADERS  += qcgenerator.h \
    timer.h

FORMS    += qcgenerator.ui

INCLUDEPATH += $$PWD/../QcUtility

TRANSLATIONS = qubic_pl_PL.ts

PWD = $$PWD/..
OUT_PWD = $$PWD/..

RCC_DIR = "$$OUT_PWD/build/RCCFiles"
UI_DIR = "$$OUT_PWD/build/UICFiles"
MOC_DIR = "$$OUT_PWD/build/MOCFiles"
OBJECTS_DIR = "$$OUT_PWD/build/ObjFiles"
QMAKE_LIBDIR_QT = $$QMAKESPEC/../../bin
DESTDIR = "$$OUT_PWD/out"

CONFIG(debug, debug|release) {
    TARGET = TestingFacilityd
    LIBS += -L$$PWD/../include \
        -lQcUtilityd
    libstocopy.path = $$DESTDIR
    libstocopy.files += \
                       $$QMAKE_LIBDIR_QT/Qt5OpenGLd.dll \
                       $$QMAKE_LIBDIR_QT/Qt5Widgetsd.dll \
                       $$QMAKE_LIBDIR_QT/Qt5Guid.dll \
                       $$QMAKE_LIBDIR_QT/Qt5Cored.dll \
                       $$PWD/../include/QcUtilityd.dll \
                       $$QMAKE_LIBDIR_QT/Qt5Sqld.dll \
                       $$QMAKE_LIBDIR_QT/Qt5Xmld.dll \
                       $$QMAKE_LIBDIR_QT/Qt5XmlPatternsd.dll \
                       $$QMAKE_LIBDIR_QT/Qt5Networkd.dll
}
CONFIG(release, debug|release) {
    TARGET = TestingFacility
    LIBS += -L$$PWD/../include \
        -lQcUtility
    libstocopy.path = $$DESTDIR
    libstocopy.files += \
                       $$QMAKE_LIBDIR_QT/Qt5OpenGL.dll \
                       $$QMAKE_LIBDIR_QT/Qt5Widgets.dll \
                       $$QMAKE_LIBDIR_QT/Qt5Gui.dll \
                       $$QMAKE_LIBDIR_QT/Qt5Core.dll \
                       $$PWD/../include/QcUtility.dll \
                       $$QMAKE_LIBDIR_QT/Qt5Sql.dll \
                       $$QMAKE_LIBDIR_QT/Qt5Xml.dll \
                       $$QMAKE_LIBDIR_QT/Qt5XmlPatterns.dll \
                       $$QMAKE_LIBDIR_QT/Qt5Network.dll
}

win32 {
    translationscopy.path = $$DESTDIR/resources/translations
    translationscopy.files += \
                        $$PWD/qubic_pl_PL.qm
    libstocopy.files += \
                       $$QMAKE_LIBDIR_QT/icuin51.dll \
                       $$QMAKE_LIBDIR_QT/libgcc_s_dw2-1.dll \
                       $$QMAKE_LIBDIR_QT/libwinpthread-1.dll \
                       $$QMAKE_LIBDIR_QT/icuuc51.dll \
                       $$QMAKE_LIBDIR_QT/icudt51.dll \

    libstocopy.depends += copy_libstdc
    copy_libstdc.target = copy_libstdc
    copy_libstdc.commands = $(COPY) \"$$QMAKE_LIBDIR_QT\libstdc++-6.dll\" \"$${libstocopy.path}\"
    QMAKE_EXTRA_TARGETS += copy_libstdc
}



INSTALLS += libstocopy translationscopy
