AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

AM_CPPFLAGS = -I$(srcdir)/../util -I$(srcdir)/../bson  -I$(srcdir)/../filesystem -I$(srcdir)/../cache

lib_LTLIBRARIES = lib@LIB_NAME@-@DJON_DB_API_VERSION@.la

lib@LIB_NAME@_@DJON_DB_API_VERSION@_la_SOURCES = bplusindex.cpp \
                                                 dbcontroller.cpp \
                                                 indexfactory.cpp \
                                                 indexmanager.cpp \
                                                 bplusindex.h \
                                                 dbcontroller.h \
                                                 indexfactory.h \
                                                 index.h \
                                                 indexmanager.h

library_includedir=$(includedir)/@LIB_NAME@-1.0/@LIB_NAME@
#library_include_HEADERS = bson.h

@LIB_NAME@_libincludedir = $(libdir)/@LIB_NAME@-1.0/include
nodist_@LIB_NAME@_libinclude_HEADERS = config.h



