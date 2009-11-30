/* 
 * File:   mysqlstatement.h
 * Author: cross
 *
 * Created on November 26, 2009, 1:28 PM
 */

#ifndef _MYSQLSTATEMENT_H
#define	_MYSQLSTATEMENT_H

#include <map>
#include <mysql.h>

#include "../dbjaguar.h"

using namespace std;
using namespace dbjaguar;

class MySQLStatement : public Statement {
private:
    map<int, void*> m_paramValues;
    MYSQL* m_mysql;
    MYSQL_STMT* m_stmt;
    MYSQL_BIND* m_bind;

    int param_count;
public:
    MySQLStatement(MYSQL* _mysql, const char* query);
    ~MySQLStatement();
    int executeUpdate();
    void setParameter(int param, DBFIELD_TYPE type, void* value);
};

#endif	/* _MYSQLSTATEMENT_H */

