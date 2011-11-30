AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

all_includes = -I$(srcdir)/../util -I$(srcdir)/../bson  -I$(srcdir)/../filesystem -I$(srcdir)/../cache

if DEBUG
   AM_CFLAGS = -g3 -O0 $(all_includes)
   AM_CPPFLAGS = -g3 -O0 $(all_includes)
else
   AM_CFLAGS = -O2 $(all_includes)
   AM_CPPFLAGS = -O2 $(all_includes)
endif

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



