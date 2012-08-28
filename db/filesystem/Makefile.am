AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

all_includes = -I$(srcdir)/../util -I$(srcdir)/../bson

include $(top_srcdir)/common.mk

AM_CFLAGS += $(all_includes)
AM_CPPFLAGS += $(all_includes)

lib_LTLIBRARIES = libdjon-filesystem.la

libdjon_filesystem_la_SOURCES = bsoninputstream.cpp \
                                                         bsonoutputstream.cpp \
                                                         fileinputoutputstream.cpp \
                                                         fileinputstream.cpp \
                                                         fileoutputstream.cpp \
                                                         networkinputstream.cpp \
                                                         networkoutputstream.cpp \
                                                         bsoninputstream.h \
                                                         bsonoutputstream.h \
                                                         defs.h \
                                                         fileinputoutputstream.h \
                                                         fileinputstream.h \
                                                         fileoutputstream.h \
                                                         inputstream.h \
                                                         networkinputstream.h \
                                                         networkoutputstream.h \
                                                         outputstream.h

TESTS = test-filesystem
check_PROGRAMS = test-filesystem
test_filesystem_LDADD = libdjon-filesystem.la -ldjon-bson -ldjon-util -lpthread -lX11 -lXss -lrt -luuid -lcpptest
test_filesystem_SOURCES = tests/main.cpp


djon_filesystem_libincludedir = $(libdir)/djon-filesystem-1.0/include
#nodist_djon_filesystem_libinclude_HEADERS = config.h


