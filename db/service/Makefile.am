AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

AM_CPPFLAGS = -I$(srcdir)/../network

lib_LTLIBRARIES = lib@LIB_NAME@-@DJON_SERVICE_API_VERSION@.la

lib@LIB_NAME@_@DJON_SERVICE_API_VERSION@_la_SOURCES = service.h \
                                                      service.cpp

library_includedir=$(includedir)/@LIB_NAME@-1.0/@LIB_NAME@
library_include_HEADERS = service.h

@LIB_NAME@_libincludedir = $(libdir)/@LIB_NAME@-1.0/include
nodist_@LIB_NAME@_libinclude_HEADERS = config.h



