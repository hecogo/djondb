AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

AM_CPPFLAGS = -I$(srcdir)/../util -I$(srcdir)/../bson

lib_LTLIBRARIES = lib@LIB_NAME@-@DJON_CACHE_API_VERSION@.la

lib@LIB_NAME@_@DJON_CACHE_API_VERSION@_la_SOURCES = cachemanager.cpp \
                                                    structure.cpp \
                                                    structure.h \
                                                    cachemanager.h \
                                                    cache.h

library_includedir=$(includedir)/@LIB_NAME@-1.0/@LIB_NAME@
library_include_HEADERS = cache.h

@LIB_NAME@_libincludedir = $(libdir)/@LIB_NAME@-1.0/include
nodist_@LIB_NAME@_libinclude_HEADERS = config.h



