#-------------------------------------------------
#
# Project created by QtCreator 2013-09-12T00:43:58
#
#-------------------------------------------------

QT       += core widgets sql xml

QT       -= gui

TARGET = TestingFacility
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += c++11

TEMPLATE = app


SOURCES += main.cpp

INCLUDEPATH += $$PWD/../QcCore \
               $$PWD/../QcUtility

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
        -lQcUtilityd -lQcCored
    libstocopy.path = $$DESTDIR
    libstocopy.files += \
                       $$QMAKE_LIBDIR_QT/Qt5OpenGLd.dll \
                       $$QMAKE_LIBDIR_QT/Qt5Widgetsd.dll \
                       $$QMAKE_LIBDIR_QT/Qt5Guid.dll \
                       $$QMAKE_LIBDIR_QT/Qt5Cored.dll \
                       $$PWD/../include/QcUtilityd.dll \
                       $$PWD/../include/QcCored.dll
}
CONFIG(release, debug|release) {
    TARGET = TestingFacility
    LIBS += -L$$PWD/../include \
        -lQcUtility -lQcCore
    libstocopy.path = $$DESTDIR
    libstocopy.files += \
                       $$QMAKE_LIBDIR_QT/Qt5OpenGL.dll \
                       $$QMAKE_LIBDIR_QT/Qt5Widgets.dll \
                       $$QMAKE_LIBDIR_QT/Qt5Gui.dll \
                       $$QMAKE_LIBDIR_QT/Qt5Core.dll \
                       $$PWD/../include/QcUtility.dll \
                       $$PWD/../include/QcCore.dll
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
