#include <iostream>
#include "dbjaguar.h"

using namespace std;
using namespace dbjaguar;

int testConnection()
{
    ConnectionPool* pool = new ConnectionPool();
    try
    {
        Connection* con = pool->getConnection("mysql;localhost;3304;mangos", "root", "cross2000");
        con->close();
    }
    catch (DBException e)
    {
        cout << e.what() << endl;
        return 1;
    }
    return 0;
}

int testResultSet()
{
    ConnectionPool* pool = new ConnectionPool();
    Connection* con = NULL;
    ResultSet* rs = NULL;
    try
    {
        con = pool->getConnection("mysql;localhost;3304;mangos", "root", "cross2000");
        rs = con->executeQuery("SELECT name, modelid_A, minlevel, speed, scriptname FROM creature_template limit 0, 10");
        // char, medium int, tiny, float, smallint,integer,null
        int x = 0;
        cout << "Name\t\t\tmodelid\tminlevel\tspeed\tscriptname" << endl;
        while ((*rs)++)
        {
            string* name = (string*)rs->get(0);
            int* modelid_A = (int*)rs->get(1);
            int* minlevel = (int*)rs->get(2);
            float* speed = (float*)rs->get(3);
            string* scriptname = (string*)rs->get(4);
            cout << *((string*)name) << "\t\t\t" << *modelid_A << "\t" << *minlevel << "\t" << *speed << "\t" << *scriptname << endl;
        }
    }
    catch (DBException e)
    {
        cout << e.what() << endl;
        return 1;
    }
    if (rs)
        rs->close();
    if (con)
        con->close();
    return 0;
}

int testUpdate()
{
    ConnectionPool* pool = new ConnectionPool();
    try
    {
        Connection* con = pool->getConnection("mysql;localhost;3304;mangos", "root", "cross2000");
        con->executeUpdate("CREATE TABLE test ( name int)");
        con->executeUpdate("INSERT INTO test (name) values ('test')");
        con->executeUpdate("DROP TABLE test");
        con->close();
    }
    catch (DBException& e)
    {
        cout << e.what() << endl;
        return 1;
    }
    return 0;
}

int main()
{
    if (testConnection())
    {
        return 1;
    }
    if (testResultSet())
    {
        return 1;
    }
    if (testUpdate())
    {
        return 1;
    }
    return 0;
}
