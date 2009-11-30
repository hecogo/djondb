#include "mysqlcommon.h"
#include <mysql/mysql.h>

using namespace dbjaguar;

enum_field_types getMySQLType(dbjaguar::DBFIELD_TYPE type) {
    switch (type) {
        case DBTYPE_BLOB:
            return MYSQL_TYPE_BLOB;
        case DBTYPE_CHAR:
            return MYSQL_TYPE_VARCHAR;
        case DBTYPE_DATE:
            return MYSQL_TYPE_DATE;
        case DBTYPE_DATETIME:
            return MYSQL_TYPE_DATETIME;
        case DBTYPE_DECIMAL:
            return MYSQL_TYPE_DECIMAL;
        case DBTYPE_DOUBLE:
            return MYSQL_TYPE_DOUBLE;
        case DBTYPE_FLOAT:
            return MYSQL_TYPE_FLOAT;
        case DBTYPE_INT24:
            return MYSQL_TYPE_INT24;
        case DBTYPE_LONG:
            return MYSQL_TYPE_LONG;
        case DBTYPE_SHORT:
            return MYSQL_TYPE_SHORT;
        case DBTYPE_STRING:
            return MYSQL_TYPE_STRING;
        case DBTYPE_TIME:
            return MYSQL_TYPE_TIME;
        case DBTYPE_TIMESTAMP:
            return MYSQL_TYPE_TIMESTAMP;
        case DBTYPE_TINY:
            return MYSQL_TYPE_TINY;
        case DBTYPE_VAR_STRING:
            return MYSQL_TYPE_VAR_STRING;
        default:
            throw DBException(new string("type unsupported"));
    }
}
