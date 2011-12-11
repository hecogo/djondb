AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

all_includes = -I$(srcdir)/../util -I$(srcdir)/../bson  -I$(srcdir)/../filesystem -I$(srcdir)/../cache

if DEBUG
   AM_CFLAGS = -g3 -O0 $(all_includes)
   AM_CPPFLAGS = -g3 -O0 $(all_includes)
else
   AM_CFLAGS = -O2 $(all_includes)
   AM_CPPFLAGS = -O2 $(all_includes)
endif

lib_LTLIBRARIES = lib@LIB_NAME@.la

lib@LIB_NAME@_la_SOURCES = bplusindex.cpp \
                                                 dbcontroller.cpp \
                                                 indexfactory.cpp \
                                                 indexmanager.cpp \
                                                 bplusindex.h \
                                                 dbcontroller.h \
                                                 indexfactory.h \
                                                 index.h \
                                                 indexmanager.h

library_includedir=$(includedir)/@LIB_NAME@-1.0/@LIB_NAME@
#library_include_HEADERS = bson.h

TESTS = test-db
check_PROGRAMS = test-db
test_db_LDADD = lib@LIB_NAME@.la -ldjon-bson -ldjon-util -ldjon-db -ldjon-cache -ldjon-bson -ldjon-filesystem -lX11 -lXss -lrt -luuid -lantlr3c -lcpptest 
test_db_SOURCES = tests/main.cpp

@LIB_NAME@_libincludedir = $(libdir)/@LIB_NAME@-1.0/include
nodist_@LIB_NAME@_libinclude_HEADERS = config.h



