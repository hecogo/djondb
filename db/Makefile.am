ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}
SUBDIRS = util bson cache filesystem db command network tx driverbase service daemon shell

if DEBUG
   AM_CFLAGS = -g3 -O0
   AM_CPPFLAGS = -g3 -O0
else
   AM_CFLAGS = -O2
   AM_CPPFLAGS = -O2
endif

#include aminclude.am

