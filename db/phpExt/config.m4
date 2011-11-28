PHP_ARG_ENABLE(djonPhpExt,
    [Whether to enable the "djonPhpExt" extension],
    [  --enable-djonPhpExt      Enable "djonPhpExt" extension support])

if test $PHP_DJONPHPEXT != "no"; then
    PHP_REQUIRE_CXX()
    PHP_SUBST(DRIVERBASE_SHARED_LIBADD)
    PHP_ADD_INCLUDE("../bson")
    PHP_ADD_INCLUDE("../util")
    PHP_ADD_LIBRARY(stdc++, 1, DRIVERBASE_SHARED_LIBADD)
    PHP_ADD_LIBRARY(djon-client, 1, DJON_CLIENT_SHARED_LIBADD)
    PHP_NEW_EXTENSION(djonPhpExt, djonphpext.cpp, $ext_shared)
fi
