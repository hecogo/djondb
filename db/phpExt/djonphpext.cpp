#include "php_djonphpext.h"
#include "../driverbase/djondb_client.h"

PHP_MINIT_FUNCTION(djonPhpExt)
{
    return SUCCESS;
}

zend_module_entry djonPhpExt_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_DJONPHPEXT_EXTNAME,
    NULL,                  /* Functions */
    PHP_MINIT(djonPhpExt),
    NULL,                  /* MSHUTDOWN */
    NULL,                  /* RINIT */
    NULL,                  /* RSHUTDOWN */
    NULL,                  /* MINFO */
#if ZEND_MODULE_API_NO >= 20010901
    PHP_DJONPHPEXT_EXTVER,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_DJONPHPEXT
extern "C" {
ZEND_GET_MODULE(djonPhpExt)
}
#endif
