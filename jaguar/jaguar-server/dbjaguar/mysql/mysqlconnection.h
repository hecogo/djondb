#ifndef _MYSQLCONNECTION_H
#define	_MYSQLCONNECTION_H

#include <mysql.h>
#include "../dbjaguar.h"

using namespace dbjaguar;

class MySQLConnection : public Connection
{
private:
    MYSQL* m_mysql;

public:
    void open(const char* _connectiondef, const char* username, const char* password) throw (DBException);
    void close() throw (DBException);
    ResultSet* executeQuery(const char* query) throw (DBException);
    int executeUpdate(const char* query) throw (DBException);
    Statement* createStatement(const char* query) throw (DBException);
};

#endif	/* _MYSQLCONNECTION_H */

