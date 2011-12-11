AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

all_includes = -I$(srcdir)/../util -I$(srcdir)/../bson

if DEBUG
   AM_CFLAGS = -g3 -O0 $(all_includes)
   AM_CPPFLAGS = -g3 -O0 $(all_includes)
else
   AM_CFLAGS = -O2 $(all_includes)
   AM_CPPFLAGS = -O2 $(all_includes)
endif


lib_LTLIBRARIES = lib@LIB_NAME@.la

lib@LIB_NAME@_la_SOURCES = cachemanager.cpp \
                                                    structure.cpp \
                                                    structure.h \
                                                    cachemanager.h \
                                                    cache.h

library_includedir=$(includedir)/@LIB_NAME@-1.0/@LIB_NAME@
library_include_HEADERS = cache.h

TESTS = test-cache
check_PROGRAMS = test-cache
test_cache_LDADD = lib@LIB_NAME@.la -lX11 -lXss -lrt -luuid -lantlr3c -lcpptest -ldjon-bson -ldjon-util
test_cache_SOURCES = tests/main.cpp

@LIB_NAME@_libincludedir = $(libdir)/@LIB_NAME@-1.0/include
nodist_@LIB_NAME@_libinclude_HEADERS = config.h



