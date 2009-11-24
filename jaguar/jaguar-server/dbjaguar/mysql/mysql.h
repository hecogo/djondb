#include "../dbjaguar.h"
#include <mysql.h>
#include <map>

using namespace dbjaguar;

class MySQLConnection;
class MySQLResultSet;

class MySQLResultSet : public ResultSet
{
private:
    MYSQL_FIELD** m_res_fields;
    int m_res_numfields;
    map<string, int> m_res_fieldsByName;
    MYSQL_RES* m_res;
    const char* m_query;
    MYSQL_ROW m_currentRow;
public:
    MySQLResultSet(MYSQL_RES* res, const char* query);
    bool next() throw (DBException);
    bool previous() throw (DBException);
    void close() throw (DBException);
    void* get(int col) throw (DBException);
    void* get(const char* colname) throw (DBException);
};

class MySQLConnection : public Connection
{
private:
    MYSQL* m_mysql;

public:
    void open(const char* _connectiondef, const char* username, const char* password) throw (DBException);
    void close() throw (DBException);
    ResultSet* executeQuery(const char* query) throw (DBException);
    int executeUpdate(const char* query) throw (DBException);

};
