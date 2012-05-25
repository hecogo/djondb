AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

all_includes = -I/usr/include/mongo -I$(srcdir)/../../util -I$(srcdir)/../../bson -I$(srcdir)/../../filesystem

if DEBUG
   AM_CFLAGS = -g3 -O0 $(all_includes)
   AM_CPPFLAGS = -g3 -O0 $(all_includes)
else
   AM_CFLAGS = -O2 $(all_includes)
   AM_CPPFLAGS = -O2 $(all_includes)
endif

bin_PROGRAMS = testmongo
testmongo_SOURCES = main.cpp
testmongo_LDADD = -lmongoclient -lboost_thread -lboost_system -lboost_filesystem -lboost_program_options  -ldjon-filesystem -ldjon-bson -ldjon-util -lXss -luuid -lrt
# djondbd_LDADD = $(top_builddir)/service/libdjon-service.la $(top_builddir)/network/libdjon-network.la $(top_builddir)/command/libdjon-command.la $(top_builddir)/db/libdjon-db.la $(top_builddir)/filesystem/libdjon-filesystem.la $(top_builddir)/cache/libdjon-cache.la $(top_builddir)/bson/libdjon-bson.la $(top_builddir)/util/libdjon-util.la -lX11 -lXss -lrt -luuid

