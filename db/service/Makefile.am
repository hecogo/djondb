AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

all_includes = -I$(srcdir)/../network

if DEBUG
   AM_CFLAGS = -g3 -O0 $(all_includes)
   AM_CPPFLAGS = -g3 -O0 $(all_includes)
else
   AM_CFLAGS = -O2 $(all_includes)
   AM_CPPFLAGS = -O2 $(all_includes)
endif

lib_LTLIBRARIES = libdjon-service.la

libdjon_service_la_SOURCES = service.h \
                           service.cpp

TESTS = test-service
check_PROGRAMS = test-service
test_service_LDADD = libdjon-service.la -ldjon-network -ldjon-command -ldjon-db -ldjon-filesystem -ldjon-cache -ldjon-bson -ldjon-util -lX11 -lXss -lrt -luuid -lantlr3c -lcpptest 
test_service_SOURCES = tests/main.cpp

library_includedir=$(includedir)/djon-service-1.0/djon-service
library_include_HEADERS = service.h

djon_service_libincludedir = $(libdir)/djon-service-1.0/include
#nodist_djon_service_libinclude_HEADERS = config.h



