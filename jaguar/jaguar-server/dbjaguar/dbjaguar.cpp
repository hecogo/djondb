
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
map<string, int> keys;
ConnectionPool* m_pool;


void ConnectionPool::initializeConnectionPool() {
}

ConnectionPool::ConnectionPool() {
    initializeConnectionPool();
}

Connection* ConnectionPool::getConnection(const char* _connectionDef, const char* username, const char* password) throw (DBException) {
    Connection* connection = new MySQLConnection();
    connection->open(_connectionDef, username, password);
    return connection;
}

int getNextKey(string table) {
    map<string, int>::iterator iter = keys.find(table);
    if (iter == keys.end()) {
        pair < map<string, int>::iterator, bool> res = keys.insert(pair<string, int>(table, 0));
        if (res.second) {
            iter = res.first;
        } else {
            iter = keys.find(table);
        }
    }
    int key = ++iter->second;
    return key;
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
    delete(m_pool);
}