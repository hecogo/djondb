AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

all_includes = -I$(srcdir)/../bson -I$(srcdir)/../util -I$(srcdir)/../filesystem -I$(srcdir)/../command

if DEBUG
   AM_CFLAGS = -g3 -O0 $(all_includes)
   AM_CPPFLAGS = -g3 -O0 $(all_includes)
else
   AM_CFLAGS = -O2 $(all_includes)
   AM_CPPFLAGS = -O2 $(all_includes)
endif

lib_LTLIBRARIES = lib@LIB_NAME@.la

lib@LIB_NAME@_la_SOURCES = connection.cpp \
                                                     connection.h \
                                                     connectionmanager.cpp \
                                                     connectionmanager.h \
                                                     djondb_client.h

TESTS = test-driverbase
check_PROGRAMS = test-driverbase
test_driverbase_LDADD = lib@LIB_NAME@.la -ldjon-command -ldjon-db -ldjon-filesystem -ldjon-cache -ldjon-bson -ldjon-util -lX11 -lXss -lrt -luuid -lantlr3c -lcpptest 
test_driverbase_SOURCES = tests/main.cpp

@LIB_NAME@_libincludedir = $(libdir)/@LIB_NAME@-1.0/include
nodist_@LIB_NAME@_libinclude_HEADERS = config.h
