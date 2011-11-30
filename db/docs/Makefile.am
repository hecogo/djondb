AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

all_includes = $(AM_CPPFLAGS) -I$(srcdir)/../util -I$(srcdir)/../bson

if DEBUG
   AM_CFLAGS = -g3 -O0 $(all_includes)
   AM_CPPFLAGS = -g3 -O0 $(all_includes)
else
   AM_CFLAGS = -O2 $(all_includes)
   AM_CPPFLAGS = -O2 $(all_includes)
endif


lib_LTLIBRARIES = lib@LIB_NAME@-@DJON_UTIL_API_VERSION@.la

lib@LIB_NAME@_@DJON_UTIL_API_VERSION@_la_SOURCES = util.cpp \
                                                   util/fileutil.cpp \
                                                   util/version.cpp \
                                                   util/threads.cpp \
                                                   util/dtime.cpp \
                                                   util/stringfunctions.cpp \
                                                   util/errorHandle.cpp \
                                                   util/logger.cpp \
                                                   util/DateTime.cpp \
                                                   util.h \
                                                   config.h \
                                                   util/DateTime.h \
                                                   util/errorHandle.h \
                                                   util/dtime.h \
                                                   util/fileutil.h \
                                                   util/logger.h \
                                                   util/version.h \
                                                   util/stringfunctions.h \
                                                   util/threads.h

library_includedir=$(includedir)/@LIB_NAME@-1.0/@LIB_NAME@
library_include_HEADERS = util.h

@LIB_NAME@_libincludedir = $(libdir)/@LIB_NAME@-1.0/include
nodist_@LIB_NAME@_libinclude_HEADERS = config.h


