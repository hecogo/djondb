AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

all_includes = -I$(srcdir)/../util

if DEBUG
   AM_CFLAGS = -g3 -O0 $(all_includes)
   AM_CPPFLAGS = -g3 -O0 $(all_includes)
else
   AM_CFLAGS = -O2 $(all_includes)
   AM_CPPFLAGS = -O2 $(all_includes)
endif

lib_LTLIBRARIES = lib@LIB_NAME@.la

lib@LIB_NAME@_la_SOURCES = bsonobj.cpp \
                           bsonobj.h \
									bsoncontent.h \
									defs.h \
									bsoncontent.cpp \
                           bson.h \
                           bsonparser.cpp \
                           bsonparser.h \
                           JSONGrammarLexer.c \
                           JSONGrammarLexer.h \
                           JSONGrammarParser.c \
                           JSONGrammarParser.h

library_includedir=$(includedir)/@LIB_NAME@-1.0/@LIB_NAME@
library_include_HEADERS = bson.h

TESTS = test-bson
bin_PROGRAMS = test-bson
check_PROGRAMS = test-bson
test_bson_LDADD = lib@LIB_NAME@.la -ldjon-util -lX11 -lXss -lrt -luuid   -lantlr3c -lcpptest
test_bson_SOURCES = tests/main.cpp

@LIB_NAME@_libincludedir = $(libdir)/@LIB_NAME@-1.0/include
nodist_@LIB_NAME@_libinclude_HEADERS = config.h
