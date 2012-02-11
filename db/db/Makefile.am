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

lib_LTLIBRARIES = libdjon-db.la

libdjon_db_la_SOURCES = bplusindex.cpp \
                                                 dbcontroller.cpp \
                                                 indexfactory.cpp \
                                                 indexmanager.cpp \
                                                 bplusindex.h \
                                                 dbcontroller.h \
                                                 indexfactory.h \
                                                 index.h \
                                                 indexmanager.h

library_includedir=$(includedir)/djon-db-1.0/djon-db
#library_include_HEADERS = bson.h

TESTS = test-db
check_PROGRAMS = test-db
test_db_LDADD = libdjon-db.la -ldjon-filesystem -ldjon-cache -ldjon-bson -ldjon-util -lX11 -lXss -lrt -luuid -lcpptest
test_db_SOURCES = tests/main.cpp

djon_db_libincludedir = $(libdir)/djon-db-1.0/include
#nodist_djon_db_libinclude_HEADERS = config.h


