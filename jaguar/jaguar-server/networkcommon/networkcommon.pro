#-------------------------------------------------
#
# Project created by QtCreator 2011-03-29T22:44:22
#
#-------------------------------------------------

QT       -= core gui

TARGET = networkcommon
TEMPLATE = lib

DESTDIR = ../../lib

INCLUDEPATH += . \
    net \
    ../common

DEFINES += NETWORKCOMMON_LIBRARY

SOURCES += \
    networkclient.cpp \
    net/response.cpp \
    net/request.cpp

HEADERS +=\
        networkcommon_global.h \
    networkclient.h \
    net/response.h \
    net/request.h \
    net/defs.h
