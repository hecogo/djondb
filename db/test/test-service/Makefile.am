AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

all_includes = -I$(srcdir)/../../util -I$(srcdir)/../../bson  -I$(srcdir)/../../filesystem -I$(srcdir)/../../cache  -I$(srcdir)/../../service

if DEBUG
   AM_CFLAGS = -g3 -O0 $(all_includes)
   AM_CPPFLAGS = -g3 -O0 $(all_includes)
else
   AM_CFLAGS = -O2 $(all_includes)
   AM_CPPFLAGS = -O2 $(all_includes)
endif

bin_PROGRAMS = test-service
test_service_SOURCES = main.cpp




