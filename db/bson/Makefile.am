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
			  bsoncontent.cpp \
			  bson.h \
			  bsonparser.cpp \
			  bsonparser.h

library_includedir=$(includedir)/djondb_0.1
library_include_HEADERS = bson.h bsonobj.h bsonparser.h bsondefs.h bsoncontent.h bsonarrayobj.h

TESTS = test-bson
bin_PROGRAMS = test-bson test-performance
check_PROGRAMS = test-bson
test_bson_LDADD = libdjon-bson.la $(top_builddir)/util/libdjon-util.la -lX11 -lXss -lcpptest
if !MAC
     test_bson_LDADD += -lrt -luuid
else
endif
test_bson_SOURCES = tests/main.cpp

test_performance_SOURCES = tests/testperformance.cpp
test_performance_LDADD = libdjon-bson.la $(top_builddir)/util/libdjon-util.la -lX11 -lXss
if !MAC
     test_performance_LDADD += -lrt -luuid
endif
