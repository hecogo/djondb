#include "php_djonphpext.h"
#include "../driverbase/djondb_client.h"
#include <iostream>

using namespace std;
using namespace djondb;

zend_object_handlers connection_object_handlers;
zend_class_entry *connection_ce;

struct connection_object {
    zend_object std;
    Connection *conn;
};

void connection_free_storage(void *object TSRMLS_DC)
{
    cout << "connection_free_storage" << endl;
    connection_object *obj = (connection_object *)object;
    obj->conn->close();
    delete obj->conn;

    zend_hash_destroy(obj->std.properties);
    FREE_HASHTABLE(obj->std.properties);

    efree(obj);
}

zend_object_value connection_create_handler(zend_class_entry *type TSRMLS_DC)
{
    cout << "connection_create_handler" << endl;
    zval *tmp;
    zend_object_value retval;

    connection_object *obj = (connection_object *)emalloc(sizeof(connection_object));
    memset(obj, 0, sizeof(connection_object));
    obj->std.ce = type;

    ALLOC_HASHTABLE(obj->std.properties);
    zend_hash_init(obj->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
    zend_hash_copy(obj->std.properties, &type->default_properties,
        (copy_ctor_func_t)zval_add_ref, (void *)&tmp, sizeof(zval *));

    retval.handle = zend_objects_store_put(obj, NULL,
        connection_free_storage, NULL TSRMLS_CC);
    retval.handlers = &connection_object_handlers;

    return retval;
}

PHP_METHOD(Connection, __construct)
{
    cout << "__construct" << endl;
    char* host;
    int host_len;
    Connection *conn = NULL;
    zval *object = getThis();

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &host, &host_len) == FAILURE) {
        RETURN_NULL();
    }

    Connection* con = ConnectionManager::getConnection(host);
    if (con->open()) {
        cout << "Connection open. host:" << host << endl;
    }
    connection_object *obj = (connection_object *)zend_object_store_get_object(object TSRMLS_CC);
    obj->conn = con;
}

PHP_METHOD(Connection, djon_insert)
{
    cout << "insert" << endl;
    char* ns;
    int ns_len;
    char* json;
    int json_len;

    zval *object = getThis();

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &ns, &ns_len, &json, &json_len) == FAILURE) {
        RETURN_NULL();
    }

    connection_object *obj = (connection_object *)zend_object_store_get_object(object TSRMLS_CC);
    if (!obj) {
        cout << "obj is null" << endl;
    }
    Connection* conn = obj->conn;
    if (!conn) {
        cout << "conn is null" << endl;
    }
    conn->insert(ns, json);
}

PHP_METHOD(Connection, djon_find)
{
    char* ns;
    int ns_len;
    char* json;
    int json_len;

    zval *object = getThis();

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &ns, &ns_len, &json, &json_len) == FAILURE) {
        RETURN_NULL();
    }

    connection_object *obj = (connection_object *)zend_object_store_get_object(object TSRMLS_CC);
    Connection* conn = obj->conn;
    conn->findByKey(ns, json);
}

function_entry connection_methods[] = {
    PHP_ME(Connection,  __construct,     NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(Connection,  djon_insert,           NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Connection,  djon_find,      NULL, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

PHP_MINIT_FUNCTION(djonPhpExt)
{
    cout << "minit" << endl;
    zend_class_entry conn;
    INIT_CLASS_ENTRY(conn, "Connection", connection_methods);
    connection_ce = zend_register_internal_class(&conn TSRMLS_CC);
    connection_ce->create_object = connection_create_handler;
    memcpy(&connection_object_handlers,
        zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    connection_object_handlers.clone_obj = NULL;
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
