#-------------------------------------------------
#
# Project created by QtCreator 2011-03-29T23:11:49
#
#-------------------------------------------------

TARGET = jclientgen
TEMPLATE = lib

DESTDIR = ../lib

DEFINES += JCLIENTGEN_LIBRARY

INCLUDEPATH += . \
    ../jaguarui \
    ../../jaguar-server/networkcommon

SOURCES += \
    Radicacion.cpp \
    Clientes.cpp \
    base.cpp \
    process/RequestNewRadicacion.cpp \
    process/RequestNewCustomer.cpp

HEADERS +=\
        jclientgen_global.h \
    Radicacion.h \
    Clientes.h \
    base.h \
    process/RequestNewRadicacion.h \
    process/RequestNewCustomer.h
