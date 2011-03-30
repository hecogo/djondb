#-------------------------------------------------
#
# Project created by QtCreator 2011-03-29T22:55:51
#
#-------------------------------------------------

QT       += core

QT       -= gui

DESTDIR = ../../lib

INCLUDEPATH += . \
    ../common \
    ../networkservice \
    ../networkcommon

LIBS += -L../../lib
LIBS += -lnetworkservice
LIBS += -lnetworkcommon
LIBS += -lcommon
LIBS += -lworkflow
LIBS += -ldbjaguar
LIBS += -lmysqlclient
LIBS += -ldatamanager

TARGET = jaguar
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp
