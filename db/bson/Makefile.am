AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

all_includes = -I$(srcdir)/../util

include $(top_srcdir)/common.mk

AM_CFLAGS += $(all_includes)
AM_CPPFLAGS += $(all_includes)

lib_LTLIBRARIES = libdjon-bson.la

libdjon_bson_la_SOURCES = bsonobj.cpp \
                           bsonobj.h \
									bsonarrayobj.cpp \
									bsonarrayobj.h \
									bsoncontent.h \
									defs.h \
									bsoncontent.cpp \
                           bson.h \
                           bsonparser.cpp \
                           bsonparser.h

library_includedir=$(includedir)/djon-bson-1.0/djon-bson
library_include_HEADERS = bson.h

TESTS = test-bson
bin_PROGRAMS = test-bson
check_PROGRAMS = test-bson
if !MAC
test_bson_LDADD = libdjon-bson.la $(top_builddir)/util/libdjon-util.la -lX11 -lXss -lrt -luuid   -lcpptest
else
test_bson_LDADD = libdjon-bson.la $(top_builddir)/util/libdjon-util.la -lX11 -lXss -lcpptest
endif
test_bson_SOURCES = tests/main.cpp

djon_bson_libincludedir = $(libdir)/djon-bson-1.0/include
#nodist_djon_bson_libinclude_HEADERS = config.h
