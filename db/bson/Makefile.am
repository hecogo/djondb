AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

if DEBUG
   AM_CFLAGS = -g3 -O0
   AM_CPPFLAGS = -g3 -O0
else
   AM_CFLAGS = -O2
   AM_CPPFLAGS = -O2
endif

AM_CPPFLAGS = $(AM_CPPFLAGS) -I$(srcdir)/../util

lib_LTLIBRARIES = lib@LIB_NAME@-@DJON_BSON_API_VERSION@.la

lib@LIB_NAME@_@DJON_BSON_API_VERSION@_la_SOURCES = bsonobj.cpp \
                                                     bsonobj.h \
                                                     bson.h \
                                                     bsonparser.cpp \
                                                     bsonparser.h \
                                                     JSONGrammarLexer.c \
                                                     JSONGrammarLexer.h \
                                                     JSONGrammarParser.c \
                                                     JSONGrammarParser.h

library_includedir=$(includedir)/@LIB_NAME@-1.0/@LIB_NAME@
library_include_HEADERS = bson.h

@LIB_NAME@_libincludedir = $(libdir)/@LIB_NAME@-1.0/include
nodist_@LIB_NAME@_libinclude_HEADERS = config.h
