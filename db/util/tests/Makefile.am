AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

all_includes = -I$(srcdir)/..

if DEBUG
   AM_CFLAGS = -g3 -O0 $(all_includes)
   AM_CXXFLAGS = -g3 -O0 $(all_includes)
else
   AM_CFLAGS = -O2 $(all_includes)
   AM_CXXFLAGS = -O2 $(all_includes)
endif

bin_PROGRAMS = test-util
test_util_SOURCES = main.cpp

