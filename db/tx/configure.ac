AC_INIT([djon-tx], [0.1], [crossleyjuan@gmail.com], [djon], [http://d-jon.com/])
AC_PREREQ([2.59])
AM_INIT_AUTOMAKE([1.10 -Wall no-define])
# AC_CONFIG_SUBDIRS(dinnerd libdinner hungryhacker vdinner)

AC_ARG_ENABLE(debug,
AS_HELP_STRING([debug],
               [enable debugging, default: no]),
[case "${enableval}" in
             yes) debug=true ;;
             no)  debug=false ;;
             *)   AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
esac],
[debug=false])

AM_CONDITIONAL(DEBUG, test x"$debug" = x"true")

AC_CONFIG_HEADERS([config.h])
LT_INIT([disable-static])
AC_PROG_CXX
AC_SUBST([DJON_DB_SO_VERSION], [0:1:0])
AC_SUBST([DJON_DB_API_VERSION], [0.1])
AC_SUBST([LIB_NAME], [djon-db])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
