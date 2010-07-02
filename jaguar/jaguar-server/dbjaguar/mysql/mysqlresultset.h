#ifndef _MYSQLRESULTSET_H
#define	_MYSQLRESULTSET_H

#include <map>
#include <mysql.h>
#include "../dbjaguar.h"

using namespace std;
using namespace dbjaguar;

class MySQLResultSet : public ResultSet
{
private:
    MYSQL_FIELD* m_res_fields;
    int m_res_numfields;
    map<string, int>* m_res_fieldsByName;
    MYSQL_RES* m_res;
    const char* m_query;
    MYSQL_ROW m_currentRow;
public:
    MySQLResultSet(MYSQL_RES* res, const char* query);
    ~MySQLResultSet();
    bool next() throw (DBException);
    bool previous() throw (DBException);
    void close() throw (DBException);
    void* get(int col) throw (DBException);
    void* get(const char* colname) throw (DBException);
    int getColumnCount();
};

#endif	/* _MYSQLRESULTSET_H */

