#include "mysql/mysql.h"

using namespace dbjaguar;

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

