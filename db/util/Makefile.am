AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

if DEBUG
   AM_CFLAGS = -g3 -O0
   AM_CXXFLAGS = -g3 -O0
else
   AM_CFLAGS = -O2
   AM_CXXFLAGS = -O2
endif

lib_LTLIBRARIES = lib@LIB_NAME@.la

lib@LIB_NAME@_la_SOURCES = util.cpp \
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
                                                   defs.h

library_includedir=$(includedir)/@LIB_NAME@-1.0/@LIB_NAME@
library_include_HEADERS = util.h


TESTS = test-util
check_PROGRAMS = test-util
test_util_LDADD = lib@LIB_NAME@.la -lX11 -lXss -lrt -luuid -lcpptest
test_util_SOURCES = tests/main.cpp


@LIB_NAME@_libincludedir = $(libdir)/@LIB_NAME@-1.0/include
# nodist_@LIB_NAME@_libinclude_HEADERS = config.h


