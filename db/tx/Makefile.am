AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

all_includes = -I$(srcdir)/../util -I$(srcdir)/../bson  -I$(srcdir)/../filesystem -I$(srcdir)/../cache -I${srcdir}/../command -I${srcdir}/../db

if DEBUG
   AM_CFLAGS = -g3 -O0 $(all_includes)
   AM_CPPFLAGS = -g3 -O0 $(all_includes)
else
   AM_CFLAGS = -O2 $(all_includes)
   AM_CPPFLAGS = -O2 $(all_includes)
endif

lib_LTLIBRARIES = libdjon-tx.la

libdjon_tx_la_SOURCES = transactionmanager.cpp \
								transactionmanager.h \
								transaction.cpp \
								transaction.h \
								tx.h

#library_includedir=$(includedir)/djon-db-1.0/djon-db
#library_include_HEADERS = bson.h

TESTS = test-tx
check_PROGRAMS = test-tx
test_tx_LDADD = libdjon-tx.la -ldjon-command -ldjon-db -ldjon-filesystem -ldjon-cache -ldjon-bson -ldjon-util -lX11 -lXss -lrt -luuid -lcpptest
test_tx_SOURCES = tests/main.cpp

#djon_db_libincludedir = $(libdir)/djon-db-1.0/include
#nodist_djon_db_libinclude_HEADERS = config.h


