AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

AM_CPPFLAGS = -I$(srcdir)/../util -I$(srcdir)/../bson -I$(srcdir)/../filesystem -I$(srcdir)/../db  

lib_LTLIBRARIES = lib@LIB_NAME@-@DJON_COMMAND_API_VERSION@.la

lib@LIB_NAME@_@DJON_COMMAND_API_VERSION@_la_SOURCES = command.cpp \
                                                   commandreader.cpp \
                                                   commandresult.cpp \
                                                   commandwriter.cpp \
                                                   findbykeycommand.cpp \
                                                   insertcommand.cpp \
                                                   updatecommand.cpp \
                                                   command.h \
                                                   commandreader.h \
                                                   commandresult.h \
                                                   commandwriter.h \
                                                   findbykeycommand.h \
                                                   insertcommand.h \
                                                   updatecommand.h

library_includedir=$(includedir)/@LIB_NAME@-1.0/@LIB_NAME@
#library_include_HEADERS = bson.h

@LIB_NAME@_libincludedir = $(libdir)/@LIB_NAME@-1.0/include
nodist_@LIB_NAME@_libinclude_HEADERS = config.h

