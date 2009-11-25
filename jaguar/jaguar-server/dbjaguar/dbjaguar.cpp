#include "mysql/mysql.h"

using namespace dbjaguar;

#include <map>

// This map will be used to retrieve the next id
map<string, int> keys;

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
        pair<map<string, int>::iterator, bool> res = keys.insert(pair<string, int>(table, 0));
        if (res.second) {
            iter = res.first;
        } else {
            iter = keys.find(table);
        }
    }
    int key = ++iter->second;
    return key;
}