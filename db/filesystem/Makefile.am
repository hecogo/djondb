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

library_includedir=$(includedir)/djon-filesystem-1.0/djon-filesystem
#library_include_HEADERS = bson.h

TESTS = test-filesystem
check_PROGRAMS = test-filesystem
test_filesystem_LDADD = libdjon-filesystem.la -ldjon-bson -ldjon-util -lpthread -lX11 -lXss -lrt -luuid -lcpptest
test_filesystem_SOURCES = tests/main.cpp


djon_filesystem_libincludedir = $(libdir)/djon-filesystem-1.0/include
#nodist_djon_filesystem_libinclude_HEADERS = config.h


