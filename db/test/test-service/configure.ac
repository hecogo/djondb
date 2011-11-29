AC_INIT([test-service], [0.1], [crossleyjuan@gmail.com], [djon], [http://d-jon.com/])
AC_PREREQ([2.59])
AM_INIT_AUTOMAKE([1.10 -Wall no-define])
# AC_CONFIG_SUBDIRS(dinnerd libdinner hungryhacker vdinner)
AC_CONFIG_HEADERS([config.h])
AC_PROG_CXX
AC_SUBST([APP_NAME], [test-service])

LIBS="$X_PRE_LIBS $X_LIBS -lX11 -ldjon-service -ldjon-network -ldjon-db -ldjon-command -ldjon-cache -ldjon-filesystem -ldjon-bson -ldjon-util -lpthread -luuid -lXss -lantlr3c -lrt"

# test_service_LDADD = ../libdinner/libdinner.la

#required headers
#AC_CHECK_HEADERS([util.h bson.h],,AC_MSG_ERROR[required header file missing])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
