ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}
SUBDIRS = util bson cache command filesystem db network driverbase service

if DEBUG
   AM_CFLAGS = -g3 -O0
   AM_CPPFLAGS = -g3 -O0
else
   AM_CFLAGS = -O2
   AM_CPPFLAGS = -O2
endif

#include aminclude.am

