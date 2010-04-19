#############################################################################
# Makefile for building: libjaguarui.so.1.0.0
# Generated by qmake (2.01a) (Qt 4.5.2) on: Sat Apr 17 23:25:39 2010
# Project:  nbproject/qt-Debug.pro
# Template: lib
# Command: /usr/bin/qmake -unix VPATH=. -o qttmp-Debug.mk nbproject/qt-Debug.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -Wall -W -D_REENTRANT -fPIC $(DEFINES)
CXXFLAGS      = -pipe -g -Wall -W -D_REENTRANT -fPIC $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -Inbproject -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -I. -Inbproject -I.
LINK          = g++
LFLAGS        = -shared -Wl,-soname,libjaguarui.so.1
LIBS          = $(SUBLIBS)  -L/usr/lib -lQtGui -lQtCore -lpthread
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -sf
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = build/Debug/GNU-Linux-x86/

####### Files

SOURCES       = ui/freeformlayout.cpp \
		ScreenBase.cpp \
		ui/CurrentDateTime.cpp \
		jaguarui.cpp \
		ui/MainWindow.cpp \
		ui/label.cpp \
		ui/GenericControl.cpp \
		ui/MenuItem.cpp \
		ui/TextSimple.cpp moc_TextSimple.cpp \
		moc_MainWindow.cpp \
		moc_ScreenBase.cpp \
		moc_CurrentDateTime.cpp
OBJECTS       = build/Debug/GNU-Linux-x86/freeformlayout.o \
		build/Debug/GNU-Linux-x86/ScreenBase.o \
		build/Debug/GNU-Linux-x86/CurrentDateTime.o \
		build/Debug/GNU-Linux-x86/jaguarui.o \
		build/Debug/GNU-Linux-x86/MainWindow.o \
		build/Debug/GNU-Linux-x86/label.o \
		build/Debug/GNU-Linux-x86/GenericControl.o \
		build/Debug/GNU-Linux-x86/MenuItem.o \
		build/Debug/GNU-Linux-x86/TextSimple.o \
		build/Debug/GNU-Linux-x86/moc_TextSimple.o \
		build/Debug/GNU-Linux-x86/moc_MainWindow.o \
		build/Debug/GNU-Linux-x86/moc_ScreenBase.o \
		build/Debug/GNU-Linux-x86/moc_CurrentDateTime.o
DIST          = /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/dll.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		nbproject/qt-Debug.pro
QMAKE_TARGET  = jaguarui
DESTDIR       = dist/Debug/GNU-Linux-x86/
TARGET        = libjaguarui.so.1.0.0
TARGETA       = dist/Debug/GNU-Linux-x86/libjaguarui.a
TARGETD       = libjaguarui.so.1.0.0
TARGET0       = libjaguarui.so
TARGET1       = libjaguarui.so.1
TARGET2       = libjaguarui.so.1.0

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: qttmp-Debug.mk  dist/Debug/GNU-Linux-x86/$(TARGET)

dist/Debug/GNU-Linux-x86/$(TARGET): ui_MainWindow.h ui_CurrentDateTime.h $(OBJECTS) $(SUBLIBS) $(OBJCOMP)  
	@$(CHK_DIR_EXISTS) dist/Debug/GNU-Linux-x86/ || $(MKDIR) dist/Debug/GNU-Linux-x86/ 
	-$(DEL_FILE) $(TARGET) $(TARGET0) $(TARGET1) $(TARGET2)
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS) $(OBJCOMP)
	-ln -s $(TARGET) $(TARGET0)
	-ln -s $(TARGET) $(TARGET1)
	-ln -s $(TARGET) $(TARGET2)
	-$(DEL_FILE) dist/Debug/GNU-Linux-x86/$(TARGET)
	-$(DEL_FILE) dist/Debug/GNU-Linux-x86/$(TARGET0)
	-$(DEL_FILE) dist/Debug/GNU-Linux-x86/$(TARGET1)
	-$(DEL_FILE) dist/Debug/GNU-Linux-x86/$(TARGET2)
	-$(MOVE) $(TARGET) $(TARGET0) $(TARGET1) $(TARGET2) dist/Debug/GNU-Linux-x86/



staticlib: $(TARGETA)

$(TARGETA): ui_MainWindow.h ui_CurrentDateTime.h $(OBJECTS) $(OBJCOMP) 
	-$(DEL_FILE) $(TARGETA) 
	$(AR) $(TARGETA) $(OBJECTS)

qttmp-Debug.mk: nbproject/qt-Debug.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/dll.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -unix VPATH=. -o qttmp-Debug.mk nbproject/qt-Debug.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/debug.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/dll.prf:
/usr/share/qt4/mkspecs/features/shared.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/libQtGui.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -unix VPATH=. -o qttmp-Debug.mk nbproject/qt-Debug.pro

dist: 
	@$(CHK_DIR_EXISTS) nbproject/build/Debug/GNU-Linux-x86/jaguarui1.0.0 || $(MKDIR) nbproject/build/Debug/GNU-Linux-x86/jaguarui1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) nbproject/build/Debug/GNU-Linux-x86/jaguarui1.0.0/ && $(COPY_FILE) --parents jaguarui.h ui/freeformlayout.h ui/TextSimple.h ui/MainWindow.h ui/label.h ui/GenericControl.h ScreenBase.h ui/CurrentDateTime.h ui/MenuItem.h nbproject/build/Debug/GNU-Linux-x86/jaguarui1.0.0/ && $(COPY_FILE) --parents ui/freeformlayout.cpp ScreenBase.cpp ui/CurrentDateTime.cpp jaguarui.cpp ui/MainWindow.cpp ui/label.cpp ui/GenericControl.cpp ui/MenuItem.cpp ui/TextSimple.cpp nbproject/build/Debug/GNU-Linux-x86/jaguarui1.0.0/ && $(COPY_FILE) --parents ui/MainWindow.ui ui/CurrentDateTime.ui nbproject/build/Debug/GNU-Linux-x86/jaguarui1.0.0/ && (cd `dirname nbproject/build/Debug/GNU-Linux-x86/jaguarui1.0.0` && $(TAR) jaguarui1.0.0.tar jaguarui1.0.0 && $(COMPRESS) jaguarui1.0.0.tar) && $(MOVE) `dirname nbproject/build/Debug/GNU-Linux-x86/jaguarui1.0.0`/jaguarui1.0.0.tar.gz . && $(DEL_FILE) -r nbproject/build/Debug/GNU-Linux-x86/jaguarui1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) dist/Debug/GNU-Linux-x86/$(TARGET) 
	-$(DEL_FILE) dist/Debug/GNU-Linux-x86/$(TARGET0) dist/Debug/GNU-Linux-x86/$(TARGET1) dist/Debug/GNU-Linux-x86/$(TARGET2) $(TARGETA)
	-$(DEL_FILE) qttmp-Debug.mk


mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_TextSimple.cpp moc_MainWindow.cpp moc_ScreenBase.cpp moc_CurrentDateTime.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_TextSimple.cpp moc_MainWindow.cpp moc_ScreenBase.cpp moc_CurrentDateTime.cpp
moc_TextSimple.cpp: ui/GenericControl.h \
		ui/TextSimple.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) ui/TextSimple.h -o moc_TextSimple.cpp

moc_MainWindow.cpp: ui_MainWindow.h \
		ui/MainWindow.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) ui/MainWindow.h -o moc_MainWindow.cpp

moc_ScreenBase.cpp: ScreenBase.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) ScreenBase.h -o moc_ScreenBase.cpp

moc_CurrentDateTime.cpp: ui_CurrentDateTime.h \
		ui/CurrentDateTime.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) ui/CurrentDateTime.h -o moc_CurrentDateTime.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_MainWindow.h ui_CurrentDateTime.h
compiler_uic_clean:
	-$(DEL_FILE) ui_MainWindow.h ui_CurrentDateTime.h
ui_MainWindow.h: ui/MainWindow.ui
	/usr/bin/uic-qt4 ui/MainWindow.ui -o ui_MainWindow.h

ui_CurrentDateTime.h: ui/CurrentDateTime.ui
	/usr/bin/uic-qt4 ui/CurrentDateTime.ui -o ui_CurrentDateTime.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

build/Debug/GNU-Linux-x86/freeformlayout.o: ui/freeformlayout.cpp ui/freeformlayout.h \
		ui/GenericControl.h \
		ui/label.h \
		ui/TextSimple.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/freeformlayout.o ui/freeformlayout.cpp

build/Debug/GNU-Linux-x86/ScreenBase.o: ScreenBase.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/ScreenBase.o ScreenBase.cpp

build/Debug/GNU-Linux-x86/CurrentDateTime.o: ui/CurrentDateTime.cpp ui/CurrentDateTime.h \
		ui_CurrentDateTime.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/CurrentDateTime.o ui/CurrentDateTime.cpp

build/Debug/GNU-Linux-x86/jaguarui.o: jaguarui.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/jaguarui.o jaguarui.cpp

build/Debug/GNU-Linux-x86/MainWindow.o: ui/MainWindow.cpp ui/MainWindow.h \
		ui_MainWindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/MainWindow.o ui/MainWindow.cpp

build/Debug/GNU-Linux-x86/label.o: ui/label.cpp ui/label.h \
		ui/GenericControl.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/label.o ui/label.cpp

build/Debug/GNU-Linux-x86/GenericControl.o: ui/GenericControl.cpp ui/GenericControl.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/GenericControl.o ui/GenericControl.cpp

build/Debug/GNU-Linux-x86/MenuItem.o: ui/MenuItem.cpp ui/MenuItem.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/MenuItem.o ui/MenuItem.cpp

build/Debug/GNU-Linux-x86/TextSimple.o: ui/TextSimple.cpp ui/TextSimple.h \
		ui/GenericControl.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/TextSimple.o ui/TextSimple.cpp

build/Debug/GNU-Linux-x86/moc_TextSimple.o: moc_TextSimple.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/moc_TextSimple.o moc_TextSimple.cpp

build/Debug/GNU-Linux-x86/moc_MainWindow.o: moc_MainWindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/moc_MainWindow.o moc_MainWindow.cpp

build/Debug/GNU-Linux-x86/moc_ScreenBase.o: moc_ScreenBase.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/moc_ScreenBase.o moc_ScreenBase.cpp

build/Debug/GNU-Linux-x86/moc_CurrentDateTime.o: moc_CurrentDateTime.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/moc_CurrentDateTime.o moc_CurrentDateTime.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

