#include "mysqlstatement.h"
#include "mysqlcommon.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#define THROWERROR_STMT() \
    string* connerror = new string("DBException: "); \
    const char* error = mysql_stmt_error(m_stmt); \
    connerror->append(error); \
    throw DBException(connerror);

MySQLStatement::MySQLStatement(MYSQL* _mysql, const char* query) : Statement(_mysql, query) {
    m_stmt = mysql_stmt_init(_mysql);
    if (m_stmt) {
        int res = mysql_stmt_prepare(m_stmt, query, strlen(query));
        if (res != 0) {
            THROWERROR_STMT();
        };
        param_count= mysql_stmt_param_count(m_stmt);
        if (param_count > 0) {
            m_bind = (MYSQL_BIND*)malloc(sizeof(MYSQL_BIND)*param_count);
            memset(m_bind, 0, sizeof(MYSQL_BIND));
        } else {
            m_bind = NULL;
        }
    } else {
        throw DBException(new string("mysql_stmt_init(), out of memory"));
    }

}

MySQLStatement::~MySQLStatement() {
}

int MySQLStatement::executeUpdate() {
    if (param_count > 0) {
        mysql_stmt_bind_param(m_stmt, m_bind);
    }
    int res = mysql_stmt_execute(m_stmt);
    if (res != 0) {
        cout << mysql_stmt_error(m_stmt) << endl;
    }
}

void MySQLStatement::setParameter(int param, DBFIELD_TYPE type, void* value) {
    if (param > param_count) {
        throw DBException(new string("test"));
    }

    enum_field_types mysqltype = getMySQLType(type);
    m_bind[param].buffer_type = mysqltype;
    m_bind[param].buffer= (char *)value;
    m_bind[param].is_null= 0;
    if ((mysqltype == MYSQL_TYPE_STRING) ||
            (mysqltype == MYSQL_TYPE_VARCHAR)) {
        long unsigned *len = new long unsigned(0);
        *len = strlen((char*)value);
        m_bind[param].length= len;
    } else {
        m_bind[param].length= 0;
    }
};

void MySQLStatement::close() {
    mysql_stmt_close(m_stmt);
    if (m_bind) {
        free(m_bind);
    }
}