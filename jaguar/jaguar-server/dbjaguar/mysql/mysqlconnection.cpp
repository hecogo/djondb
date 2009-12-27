#include <string.h>
#include <stdio.h>
#include "mysqlconnection.h"
#include "../dbjaguar.h"
#include "mysqlresultset.h"
#include "mysqlstatement.h"

using namespace std;
using namespace dbjaguar;

// connectiondef:    type;server:port;database

void MySQLConnection::open(const char* _connectiondef, const char* username, const char* password) throw (DBException) {
    m_mysql = mysql_init(NULL);

    string type;
    string server;
    string port;
    string database;
    getConnectionInfo(_connectiondef, &type, &server, &port, &database);

    if (!mysql_real_connect(m_mysql, server.c_str(), username, password, database.c_str(), 0, NULL, 0)) {
        THROWERROR();
    }
}

MySQLConnection::~MySQLConnection() {
}


void MySQLConnection::close() throw (DBException) {
    mysql_close(m_mysql);
}

ResultSet* MySQLConnection::executeQuery(const char* query) throw (DBException) {
    int queryres = mysql_real_query(m_mysql, query, strlen(query));
    if (queryres == 0) {
        MYSQL_RES *res = mysql_store_result(m_mysql);
        if (res) {
            MySQLResultSet* resultset = new MySQLResultSet(res, query);
            return resultset;
        } else {
            THROWERROR();
        }
    }
    THROWERROR();
}

int MySQLConnection::executeUpdate(const char* query) throw (DBException) {
    int queryres = mysql_real_query(m_mysql, query, strlen(query));
    if (queryres == 0) {
        int affectedRows = mysql_affected_rows(m_mysql);
        return affectedRows;
    } else {
        THROWERROR();
    }
}

Statement* MySQLConnection::createStatement(const char* query) throw (DBException) {
    MySQLStatement* statement = new MySQLStatement(m_mysql, query);
    return statement;
}