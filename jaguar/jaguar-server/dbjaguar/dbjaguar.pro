#-------------------------------------------------
#
# Project created by QtCreator 2011-03-29T22:37:07
#
#-------------------------------------------------

QT       -= core gui

TARGET = dbjaguar
TEMPLATE = lib

DESTDIR = ../../lib

DEFINES += DBJAGUAR_LIBRARY

INCLUDEPATH += . \
    mysql \
    ../common \
    /usr/include/mysql

SOURCES += \
    keys.cpp \
    dbjaguar.cpp \
    mysql/mysqlstatement.cpp \
    mysql/mysqlresulset.cpp \
    mysql/mysqlconnection.cpp \
    mysql/mysqlcommon.cpp

HEADERS +=\
        dbjaguar_global.h \
    keys.h \
    dbjaguar.h \
    mysql/mysqlstatement.h \
    mysql/mysqlresultset.h \
    mysql/mysqlconnection.h \
    mysql/mysqlcommon.h
