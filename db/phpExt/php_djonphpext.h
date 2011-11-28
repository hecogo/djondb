#ifndef PHP_DJONPHPEXT_H
#define PHP_DJONPHPEXT_H

#define PHP_DJONPHPEXT_EXTNAME  "djonPhpExt"
#define PHP_DJONPHPEXT_EXTVER   "0.1"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif 

extern "C" {
#include "php.h"
}

extern zend_module_entry djonphpext_module_entry;
#define phpext_djonphpext_ptr &djonphpext_module_entry;

#endif /* PHP_DJONPHPEXT_H */
