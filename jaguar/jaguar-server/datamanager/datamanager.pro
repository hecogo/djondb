#-------------------------------------------------
#
# Project created by QtCreator 2011-03-29T22:52:50
#
#-------------------------------------------------

QT       -= core gui

TARGET = datamanager
TEMPLATE = lib

DESTDIR = ../../lib

DEFINES += DATAMANAGER_LIBRARY

INCLUDEPATH += . \
    ../common \
    ../dbjaguar

SOURCES += \
    datamanager.cpp \
    manager/entityMD.cpp \
    manager/entity.cpp \
    manager/entitiesdeploy.cpp \
    manager/attributeMD.cpp \
    manager/da/mysqlentitydeploy.cpp \
    manager/da/entityda.cpp \
    manager/transaction/transactionmanager.cpp \
    manager/transaction/transactionentry.cpp \
    manager/transaction/transaction.cpp

HEADERS +=\
        datamanager_global.h \
    datamanager.h \
    manager/entityMD.h \
    manager/entity.h \
    manager/entitiesdeploy.h \
    manager/attributeMD.h \
    manager/da/mysqlentitydeploy.h \
    manager/da/entityda.h \
    manager/transaction/transactionmanager.h \
    manager/transaction/transactionentry.h \
    manager/transaction/transaction.h
