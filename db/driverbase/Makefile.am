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
test_driverbase_CPPFLAGS = -I$(srcdir)../driverbase
test_driverbase_LDADD = libdjon-client.la -ldjon-command -ldjon-db -ldjon-filesystem -ldjon-cache -ldjon-bson -ldjon-util -lX11 -lXss -lrt -luuid -lcpptest
test_driverbase_SOURCES = tests/main.cpp

bin_PROGRAMS = test-performance
test_performance_SOURCES = tests/testperformance.cpp
test_performance_LDADD = libdjon-client.la -ldjon-command -ldjon-db -ldjon-filesystem -ldjon-cache -ldjon-bson -ldjon-util -lX11 -lXss -lrt -luuid -lcpptest

djon_client_libincludedir = $(libdir)/djon-client-1.0/include
