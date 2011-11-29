AC_INIT([djon-network], [0.1], [crossleyjuan@gmail.com], [djon], [http://d-jon.com/])
AC_PREREQ([2.59])
AM_INIT_AUTOMAKE([1.10 -Wall no-define])
# AC_CONFIG_SUBDIRS(dinnerd libdinner hungryhacker vdinner)
AC_CONFIG_HEADERS([config.h])
LT_INIT([disable-static])
AC_PROG_CXX
AC_SUBST([DJON_NETWORK_SO_VERSION], [0:1:0])
AC_SUBST([DJON_NETWORK_API_VERSION], [0.1])
AC_SUBST([LIB_NAME], [djon-network])

# LIBS="$X_PRE_LIBS $X_LIBS -lX11 -lXext -lXmu -lXt $X_EXTRA_LIBS -lGL -lGLU -lglut -lm"

#hungryhacker_LDADD = ../libdinner/libdinner.la

#required headers
#AC_CHECK_HEADERS([util.h bson.h],,AC_MSG_ERROR[required header file missing])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
