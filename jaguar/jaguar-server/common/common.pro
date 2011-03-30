#-------------------------------------------------
#
# Project created by QtCreator 2011-03-29T22:30:37
#
#-------------------------------------------------

QT       -= core gui

TARGET = common
TEMPLATE = lib

DESTDIR = ../../lib

DEFINES += COMMON_LIBRARY

SOURCES += util.cpp \
    util/timerecord.cpp \
    util/threads.cpp \
    util/cache.cpp \
    util/logger/logger.cpp

HEADERS += common_global.h \
    util.h \
    util/timerecord.h \
    util/threads.h \
    util/cache.h \
    util/logger/logger.h
