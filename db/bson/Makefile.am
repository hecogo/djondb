AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

all_includes = -I$(srcdir)/../util

if DEBUG
   AM_CFLAGS = -g3 -O0 $(all_includes)
   AM_CPPFLAGS = -g3 -O0 $(all_includes)
else
   AM_CFLAGS = -O2 $(all_includes)
   AM_CPPFLAGS = -O2 $(all_includes)
endif

lib_LTLIBRARIES = libdjon-bson.la

libdjon_bson_la_SOURCES = bsonobj.cpp \
                           bsonobj.h \
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
test_bson_LDADD = libdjon-bson.la -ldjon-util -lX11 -lXss -lrt -luuid   -lcpptest
test_bson_SOURCES = tests/main.cpp

djon_bson_libincludedir = $(libdir)/djon-bson-1.0/include
#nodist_djon_bson_libinclude_HEADERS = config.h
