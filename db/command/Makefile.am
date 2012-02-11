AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

all_includes = -I$(srcdir)/../util -I$(srcdir)/../bson -I$(srcdir)/../filesystem -I$(srcdir)/../db  

if DEBUG
   AM_CFLAGS = -g3 -O0 $(all_includes)
   AM_CPPFLAGS = -g3 -O0 $(all_includes)
else
   AM_CFLAGS = -O2 $(all_includes)
   AM_CPPFLAGS = -O2 $(all_includes)
endif


lib_LTLIBRARIES = libdjon-command.la

libdjon_command_la_SOURCES = command.cpp \
                                                   commandreader.cpp \
                                                   commandresult.cpp \
                                                   commandwriter.cpp \
                                                   findcommand.cpp \
                                                   insertcommand.cpp \
                                                   updatecommand.cpp \
                                                   command.h \
                                                   commandreader.h \
                                                   commandresult.h \
                                                   commandwriter.h \
                                                   findcommand.h \
                                                   insertcommand.h \
                                                   updatecommand.h

TESTS = test-command
check_PROGRAMS = test-command
#test_command_LDFLAGS = $(all_includes)
test_command_LDADD = libdjon-command.la -ldjon-db -ldjon-filesystem -ldjon-cache -ldjon-bson -ldjon-util -lX11 -lXss -lrt -luuid  -lcpptest
test_command_SOURCES = tests/main.cpp

library_includedir=$(includedir)/djon-command-1.0/djon-command
#library_include_HEADERS = bson.h

djon_command_libincludedir = $(libdir)/djon-command-1.0/include
#nodist_djon_command_libinclude_HEADERS = config.h

