#include "mysql.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define THROWERROR() \
    string* connerror = new string("DBException: "); \
    const char* error = mysql_error(m_mysql); \
    connerror->append(error); \
    throw DBException(connerror);

void getConnectionInfo(const char* connectionDef, string* type, string* server, string* port, string* database) {
    int len = strlen(connectionDef);

    char* conndef = (char*)malloc(len);
    strcpy(conndef, connectionDef);

    char* ptr;
    char* delim = (char*)";";
    ptr = strtok(conndef, delim);
    type->assign(ptr);

    ptr = strtok(NULL, delim);
    server->assign(ptr);

    ptr = strtok(NULL, delim);
    port->assign(ptr);

    ptr = strtok(NULL, delim);
    database->assign(ptr);

    delete(conndef);

}

// connectiondef:    type;server:port;database
void MySQLConnection::open(const char* _connectiondef, const char* username, const char* password) throw (DBException)
{
    mysql_library_init(0, NULL, NULL);
    m_mysql = mysql_init(NULL);

    string type;
    string server;
    string port;
    string database;
    getConnectionInfo(_connectiondef, &type, &server, &port, &database);

    if (!mysql_real_connect(m_mysql, server.c_str(), username, password, database.c_str(), 0, NULL, 0))
    {
        THROWERROR();
    }
}

void MySQLConnection::close() throw (DBException)
{
    mysql_close(m_mysql);
}

ResultSet* MySQLConnection::executeQuery(const char* query) throw (DBException)
{
    int queryres = mysql_real_query(m_mysql, query, strlen(query));
    if (queryres == 0)
    {
        MYSQL_RES *res = mysql_use_result(m_mysql);
        if (res)
        {
            MySQLResultSet* resultset = new MySQLResultSet(res, query);
            return resultset;
        }
        else
        {
            THROWERROR();
        }
    }
    THROWERROR();
}

int MySQLConnection::executeUpdate(const char* query) throw (DBException)
{
    int queryres = mysql_real_query(m_mysql, query, strlen(query));
    if (queryres == 0) {
        int affectedRows = mysql_affected_rows(m_mysql);
        return affectedRows;
    } else {
        THROWERROR();
    }
}

