#-------------------------------------------------
#
# Project created by QtCreator 2017-02-09T23:34:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Netcalc
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    mac.cpp \
    ip.cpp \
    paint_mask.cpp \
    ipmask.cpp

HEADERS  += \
    mac.h \
    main.h \
    ip.h \
    paint_mask.h \
    ipmask.h

FORMS    += \
    mac.ui \
    ip.ui

QMAKE_CXXFLAGS += -std=gnu++14

RESOURCES += \
    res.qrc

RC_FILE = res.rc

DISTFILES += \
    codestyle.xml
