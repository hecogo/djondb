#-------------------------------------------------
#
# Project created by QtCreator 2011-03-29T22:47:40
#
#-------------------------------------------------

QT       -= core gui

TARGET = networkservice
TEMPLATE = lib

DESTDIR = ../../lib

DEFINES += NETWORKSERVICE_LIBRARY

INCLUDEPATH += . \
    ../common \
    ../networkcommon \
    ../dbjaguar

SOURCES += \
    networkservice.cpp \
    net/requestprocessor.cpp \
    net/controller.cpp

HEADERS +=\
        networkservice_global.h \
    networkservice.h \
    config.h \
    net/requestprocessor.h \
    net/controller.h
