TEMPLATE = lib
DESTDIR = dist/Debug/GNU-Linux-x86
TARGET = jaguarui
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += dll debug 
QT = core gui
SOURCES += ui/freeformlayout.cpp ScreenBase.cpp ui/CurrentDateTime.cpp jaguarui.cpp ui/MainWindow.cpp ui/label.cpp ui/GenericControl.cpp ui/TextSimple.cpp ui/MenuItem.cpp
HEADERS += jaguarui.h ui/freeformlayout.h ui/TextSimple.h ui/MainWindow.h ui/label.h ui/GenericControl.h ScreenBase.h ui/CurrentDateTime.h ui/MenuItem.h
FORMS += ui/MainWindow.ui ui/CurrentDateTime.ui
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/GNU-Linux-x86
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += 
LIBS += 
