AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

all_includes = -I$(srcdir)/../driverbase -I$(srcdir)/../util -I$(srcdir)/../bson
#-I$(srcdir)/../util -I$(srcdir)/../util 


if DEBUG
   AM_CFLAGS = -g3 -O0
   DB_XXFLAGS = -g3 -O0
else
   AM_CFLAGS = -O2
   DB_XXFLAGS = -O2
endif

if PROFILE
	PF_XXFLAGS = -pg   
endif

AM_CXXFLAGS = ${PF_XXFLAGS} ${DB_XXFLAGS} ${all_includes}

bin_PROGRAMS = djon-shell
djon_shell_SOURCES = shell.cpp 
djon_shell_LDADD = -ldjon-service -ldjon-client -ldjon-network -ldjon-command -ldjon-db -ldjon-filesystem -ldjon-cache -ldjon-bson -ldjon-util -lantlr3c -lX11 -lXss -lrt -luuid -lv8

