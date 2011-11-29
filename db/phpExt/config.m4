PHP_ARG_ENABLE(djonPhpExt,
    [Whether to enable the "djonPhpExt" extension],
    [  --enable-djonPhpExt      Enable "djonPhpExt" extension support])

if test $PHP_DJONPHPEXT != "no"; then
    PHP_REQUIRE_CXX()
    PHP_SUBST(DJONPHPEXT_SHARED_LIBADD)
    PHP_ADD_INCLUDE("../bson")
    PHP_ADD_INCLUDE("../util")
    PHP_ADD_LIBRARY_WITH_PATH(stdc++, /usr/lib, DJONPHPEXT_SHARED_LIBADD)
    PHP_ADD_LIBRARY_WITH_PATH(djon-client, /usr/lib, DJONPHPEXT_SHARED_LIBADD)
    PHP_ADD_LIBRARY_WITH_PATH(djon-bson, /usr/lib, DJONPHPEXT_SHARED_LIBADD)
    PHP_ADD_LIBRARY_WITH_PATH(antlr3c, /usr/lib, DJONPHPEXT_SHARED_LIBADD)
    PHP_ADD_LIBRARY_WITH_PATH(djon-command, /usr/lib, DJONPHPEXT_SHARED_LIBADD)
    PHP_NEW_EXTENSION(djonPhpExt, djonphpext.cpp, $ext_shared)
fi
