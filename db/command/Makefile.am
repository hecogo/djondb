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


lib_LTLIBRARIES = lib@LIB_NAME@-@DJON_COMMAND_API_VERSION@.la

lib@LIB_NAME@_@DJON_COMMAND_API_VERSION@_la_SOURCES = command.cpp \
                                                   commandreader.cpp \
                                                   commandresult.cpp \
                                                   commandwriter.cpp \
                                                   findbykeycommand.cpp \
                                                   insertcommand.cpp \
                                                   updatecommand.cpp \
                                                   command.h \
                                                   commandreader.h \
                                                   commandresult.h \
                                                   commandwriter.h \
                                                   findbykeycommand.h \
                                                   insertcommand.h \
                                                   updatecommand.h

library_includedir=$(includedir)/@LIB_NAME@-1.0/@LIB_NAME@
#library_include_HEADERS = bson.h

@LIB_NAME@_libincludedir = $(libdir)/@LIB_NAME@-1.0/include
nodist_@LIB_NAME@_libinclude_HEADERS = config.h

