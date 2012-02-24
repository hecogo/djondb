AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

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

AM_CXXFLAGS = ${PF_XXFLAGS} ${DB_XXFLAGS} 

lib_LTLIBRARIES = libdjon-util.la

libdjon_util_la_SOURCES = util.cpp \
                                                   util/fileutil.cpp \
                                                   util/version.cpp \
                                                   util/threads.cpp \
                                                   util/dtime.cpp \
                                                   util/stringfunctions.cpp \
                                                   util/errorHandle.cpp \
                                                   util/logger.cpp \
                                                   util/DateTime.cpp \
                                                   util.h \
                                                   config.h \
                                                   util/DateTime.h \
                                                   util/errorHandle.h \
                                                   util/dtime.h \
                                                   util/fileutil.h \
                                                   util/logger.h \
                                                   util/version.h \
                                                   util/stringfunctions.h \
                                                   util/threads.h \
																	util/settings.cpp \
																	util/settings.h \
                                                   defs.h

library_includedir=$(includedir)/djon-util-1.0/djon-util
library_include_HEADERS = util.h


TESTS = test-util
check_PROGRAMS = test-util
test_util_LDADD = libdjon-util.la -lX11 -lXss -lrt -luuid -lcpptest
test_util_SOURCES = tests/main.cpp


djon_util_libincludedir = $(libdir)/djon-util-1.0/include
# nodist_djon_util_libinclude_HEADERS = config.h


