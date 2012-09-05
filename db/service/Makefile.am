AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

all_includes = -I$(srcdir)/../network

include $(top_srcdir)/common.mk

AM_CFLAGS += $(all_includes)
AM_CPPFLAGS += $(all_includes)

lib_LTLIBRARIES = libdjon-service.la

libdjon_service_la_LDFLAGS = -static# -fPIC
libdjon_service_la_SOURCES = service.h \
                           service.cpp

library_includedir=$(includedir)/djon-service-1.0/djon-service
library_include_HEADERS = service.h

djon_service_libincludedir = $(libdir)/djon-service-1.0/include
#nodist_djon_service_libinclude_HEADERS = config.h



