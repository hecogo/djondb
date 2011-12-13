AC_INIT(djondb, 1.0, crossleyjuan@gmail.com)
    AC_CONFIG_AUX_DIR(config)
#    AC_CONFIG_SRCDIR(src/foobar.cpp)

    AM_INIT_AUTOMAKE

AC_ARG_ENABLE(debug,
AS_HELP_STRING([--enable-debug],
               [enable debugging, default: no]),
[case "${enableval}" in
             yes) debug=true ;;
             no)  debug=false ;;
             *)   AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
esac],
[debug=false])

AM_CONDITIONAL(DEBUG, test x"$debug" = x"true")

#AC_CONFIG_HEADERS([config.h])
    AC_PROG_CXX
    AC_PROG_LIBTOOL

    AC_OUTPUT(Makefile util/Makefile bson/Makefile cache/Makefile filesystem/Makefile db/Makefile command/Makefile network/Makefile driverbase/Makefile service/Makefile daemon/Makefile)

