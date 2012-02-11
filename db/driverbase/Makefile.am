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

lib_LTLIBRARIES = libdjon-client.la
libdjon_client_la_SOURCES= connection.cpp \
                                                     connection.h \
                                                     connectionmanager.cpp \
                                                     connectionmanager.h \
                                                     djondb_client.h
TESTS = test-driverbase
check_PROGRAMS = test-driverbase
test_driverbase_LDADD = libdjon-client.la -ldjon-command -ldjon-db -ldjon-filesystem -ldjon-cache -ldjon-bson -ldjon-util -lX11 -lXss -lrt -luuid -lcpptest
test_driverbase_SOURCES = tests/main.cpp

djon_client_libincludedir = $(libdir)/djon-client-1.0/include
