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


lib_LTLIBRARIES = libdjon-cache.la

libdjon_cache_la_SOURCES = cachemanager.cpp \
                                                    structure.cpp \
                                                    structure.h \
                                                    cachemanager.h \
                                                    cache.h

library_includedir=$(includedir)/djon-cache-1.0/djon-cache
library_include_HEADERS = cache.h

TESTS = test-cache
check_PROGRAMS = test-cache
test_cache_LDADD = libdjon-cache.la -lX11 -lXss -lrt -luuid -lantlr3c -lcpptest -ldjon-bson -ldjon-util
test_cache_SOURCES = tests/main.cpp

djon_cache_libincludedir = $(libdir)/djon-cache-1.0/include
#nodist_djon_cache_libinclude_HEADERS = config.h



