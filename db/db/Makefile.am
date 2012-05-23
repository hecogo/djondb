AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

all_includes = -I$(srcdir)/../util -I$(srcdir)/../bson  -I$(srcdir)/../filesystem -I$(srcdir)/../cache

include $(top_srcdir)/common.mk

AM_CFLAGS += $(all_includes)
AM_CPPFLAGS += $(all_includes)

lib_LTLIBRARIES = libdjon-db.la

libdjon_db_la_SOURCES = bplusindex.cpp \
                                                 dbcontroller.cpp \
                                                 indexfactory.cpp \
                                                 indexmanager.cpp \
																 filterparser.cpp \
																 simpleexpression.cpp \
																 constantexpression.cpp \
																 unaryexpression.cpp \
																 expressionresult.cpp \
																 binaryexpression.cpp \
                                                 bplusindex.h \
                                                 dbcontroller.h \
                                                 db.h \
                                                 indexfactory.h \
                                                 index.h \
                                                 indexmanager.h \
																 simpleexpression.h \
																 constantexpression.h \
																 unaryexpression.h \
																 binaryexpression.h \
																 filterparser.h

library_includedir=$(includedir)/djon-db-1.0/djon-db
#library_include_HEADERS = bson.h

TESTS = test-db
check_PROGRAMS = test-db
test_db_LDADD = libdjon-db.la -ldjon-filesystem -ldjon-cache -ldjon-bson -ldjon-util -lX11 -lXss -lrt -luuid -lcpptest
test_db_SOURCES = tests/main.cpp

djon_db_libincludedir = $(libdir)/djon-db-1.0/include
#nodist_djon_db_libinclude_HEADERS = config.h


