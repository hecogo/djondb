
#include <string>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dbjaguar.h"
#include "mysql/mysqlconnection.h"

using namespace std;
using namespace dbjaguar;

// This map will be used to retrieve the next id
ConnectionPool* m_pool;
int _last_errorcode;
const char* _last_error;

void dbjaguar::setLastError(int errorCode, const char* error) {
    _last_errorcode = errorCode;
    _last_error = error;
}

const char* dbjaguar::getLastError() {
    return _last_error;
}

int dbjaguar::getLastErrorCode() {
    return _last_errorcode;
}

void ConnectionPool::initializeConnectionPool() {
    mysql_library_init(0, NULL, NULL);
}

ConnectionPool::ConnectionPool() {
    initializeConnectionPool();
}

Connection* ConnectionPool::getConnection(const char* _connectionDef, const char* username, const char* password) throw (DBException) {
    Connection* connection = new MySQLConnection();
    connection->open(_connectionDef, username, password);
    return connection;
}

void getConnectionInfo(const char* connectionDef, string* type, string* server, string* port, string* database) {
    int len = strlen(connectionDef);

    char* conndef = (char*) malloc(len);
    memset(conndef, 0, len);
    memcpy(conndef, connectionDef, len);

    char* ptr;
    char* delim = (char*) ";";

    ptr = strtok(conndef, delim);
    type->assign(ptr);

    ptr = strtok(NULL, delim);
    server->assign(ptr);

    ptr = strtok(NULL, delim);
    port->assign(ptr);

    ptr = strtok(NULL, delim);
    database->assign(ptr);

    free(conndef);
}

Connection* getDefaultMDConnection() {
    if (!m_pool) {
        m_pool = new ConnectionPool();
    }
    Connection* con = m_pool->getConnection("mysql;localhost;3304;jaguarmd;", "root", "cross2000");
    return con;
}

Connection* getDefaultDataConnection() {
    if (!m_pool) {
        m_pool = new ConnectionPool();
    }
    Connection* con = m_pool->getConnection("mysql;localhost;3304;jaguardata;", "root", "cross2000");
    return con;
}

void destroyPool() {
    mysql_library_end();
    delete(m_pool);
}

