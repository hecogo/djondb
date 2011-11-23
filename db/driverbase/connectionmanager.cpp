#include "connectionmanager.h"

#include "connection.h"

using namespace djondb;

std::map<std::string, ConnectionReference> ConnectionManager::_connections;

ConnectionManager::ConnectionManager()
{
    //ctor
}

ConnectionManager::~ConnectionManager()
{
    //dtor
}

Connection* ConnectionManager::getConnection(std::string host) {
    std::map<std::string, ConnectionReference>::iterator i = _connections.find(host);
    if (i != _connections.end()) {
        ConnectionReference reference = i->second;
        reference._references++;
        if (reference._connection->isOpen()) {
            return reference._connection;
        } else {
            _connections.erase(i);
        };
    }

    Connection* conn = new Connection(host);
    ConnectionReference ref;
    ref._references = 1;
    ref._connection = conn;
    _connections.insert(pair<std::string, ConnectionReference>(host, ref));
    return conn;
}

void ConnectionManager::releaseConnection(Connection* conn) {
    std::map<std::string, ConnectionReference>::iterator i = _connections.find(conn->host());
    if (i != _connections.end()) {
        ConnectionReference reference = i->second;
        reference._references--;
        if (reference._references == 0) {
            reference._connection->internalClose();
            _connections.erase(i);
        };
    }
}
