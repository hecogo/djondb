#-------------------------------------------------
#
# Project created by QtCreator 2011-03-29T23:20:33
#
#-------------------------------------------------

QT       += core gui

TARGET = qt-jaguar
TEMPLATE = app

DESTDIR=../../lib

INCLUDEPATH += . \
    net \
    ../../jclientgen \
    ../../jaguarui

LIBS += -L../../lib
LIBS += -ljaguarui
LIBS += -ljclientgen
LIBS += -lnetworkcommon
LIBS += -lcommon

SOURCES += \
    main.cpp

HEADERS  +=

FORMS    +=
