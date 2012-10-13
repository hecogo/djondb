PHP_ARG_ENABLE(djonwrapper,
    [Whether to enable the "djonwrapper" extension],
    [  --enable-djonwrapper      Enable "djonwrapper" extension support])

OS=`uname -s`

if test $PHP_DJONWRAPPER != "no"; then
    PHP_REQUIRE_CXX()
    PHP_SUBST(DJONPHPEXT_SHARED_LIBADD)
    PHP_ADD_INCLUDE(..)
    PHP_ADD_LIBRARY_WITH_PATH(antlr3c, /usr/lib, DJONPHPEXT_SHARED_LIBADD)
    PHP_ADD_LIBRARY_WITH_PATH(stdc++, /usr/lib, DJONPHPEXT_SHARED_LIBADD)
    PHP_ADD_LIBRARY_WITH_PATH(djon-client, /usr/lib, DJONPHPEXT_SHARED_LIBADD)
if test $OS != "Darwin"; then
    PHP_ADD_LIBRARY_WITH_PATH(uuid, /usr/lib, DJONPHPEXT_SHARED_LIBADD)
fi
    PHP_NEW_EXTENSION(djonwrapper, djonphpdriver.cpp, $ext_shared)
fi
