AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

all_includes = -I$(srcdir)/../util -I$(srcdir)/../bson -I$(srcdir)/../driverbase -I/usr/lib/jvm/java-6-openjdk/include

include $(top_srcdir)/common.mk

AM_CFLAGS += $(all_includes)
AM_CPPFLAGS += $(all_includes)

lib_LTLIBRARIES = libdjon-javadriver.la

libdjon_javadriver_la_SOURCES = ConnectionManagerWrapper.cpp 
libdjon_javadriver_la_LIBADD = $(top_builddir)/driverbase/libdjon-client.la $(top_builddir)/command/libdjon-command.la $(top_builddir)/db/libdjon-db.la $(top_builddir)/filesystem/libdjon-filesystem.la $(top_builddir)/cache/libdjon-cache.la $(top_builddir)/bson/libdjon-bson.la $(top_builddir)/util/libdjon-util.la -lX11 -lXss -lrt -luuid   -lcpptest -lstdc++

library_includedir=$(includedir)/djon-javadriver-1.0/djon-javadriver
# library_include_HEADERS = Connection.h

TESTS = test-javadriver
bin_PROGRAMS = test-javadriver
check_PROGRAMS = test-javadriver
test_javadriver_LDADD = libdjon-javadriver.la $(top_builddir)/driverbase/libdjon-client.la $(top_builddir)/command/libdjon-command.la $(top_builddir)/db/libdjon-db.la $(top_builddir)/filesystem/libdjon-filesystem.la $(top_builddir)/cache/libdjon-cache.la $(top_builddir)/bson/libdjon-bson.la $(top_builddir)/util/libdjon-util.la -lX11 -lXss -lrt -luuid   -lcpptest
test_javadriver_SOURCES = tests/main.cpp

djon_bson_libincludedir = $(libdir)/djon-bson-1.0/include
#nodist_djon_bson_libinclude_HEADERS = config.h
