AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

all_includes = -I$(srcdir)/../bson -I$(srcdir)/../util -I$(srcdir)/../filesystem -I$(srcdir)/../command -I$(srcdir)/../tx

include $(top_srcdir)/common.mk

AM_CFLAGS += $(all_includes)
AM_CPPFLAGS += $(all_includes)

lib_LTLIBRARIES = libdjon-client.la
libdjon_client_la_SOURCES= connection.cpp \
                                                     connection.h \
                                                     connectionmanager.cpp \
                                                     connectionmanager.h \
                                                     djondb_client.h
TESTS = test-driverbase
check_PROGRAMS = test-driverbase
test_driverbase_CPPFLAGS = $(all_includes)
test_driverbase_LDADD = libdjon-client.la $(top_builddir)/command/libdjon-command.la $(top_builddir)/db/libdjon-db.la $(top_builddir)/filesystem/libdjon-filesystem.la $(top_builddir)/cache/libdjon-cache.la $(top_builddir)/bson/libdjon-bson.la $(top_builddir)/util/libdjon-util.la -lX11 -lXss -lcpptest
test_driverbase_SOURCES = tests/main.cpp
if !MAC
test_driverbase_LDADD += -lrt -lpthread -luuid
endif

bin_PROGRAMS = test-performance
test_performance_SOURCES = tests/testperformance.cpp
test_performance_LDADD = libdjon-client.la $(top_builddir)/command/libdjon-command.la $(top_builddir)/db/libdjon-db.la $(top_builddir)/filesystem/libdjon-filesystem.la $(top_builddir)/cache/libdjon-cache.la $(top_builddir)/bson/libdjon-bson.la $(top_builddir)/util/libdjon-util.la -lX11 -lXss -lcpptest

if !MAC
test_performance_LDADD += -lrt -lpthread -luuid
endif
library_includedir=$(includedir)/djondb_0.1
library_include_HEADERS = djondb_client.h connectionmanager.h connection.h
