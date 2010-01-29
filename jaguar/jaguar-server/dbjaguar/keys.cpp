#include "keys.h"
#include "dbjaguar.h"
#include "util.h"
#include <map>
#include <string>
#include <stdlib.h>
#include <string.h>

using namespace std;
using namespace dbjaguar;

map<string, int> keys;

int getKeyFromDB(string table) {
    Connection* con = getDefaultDataConnection();
    char* sql = (char*) malloc(100);
    memset(sql, 0, 100);
    format(sql, "SELECT value FROM key_table where id = '%s' ", table.c_str());
    ResultSet* resset = con->executeQuery(sql);
    int key;
    if (resset->next()) {
        key = *(static_cast<int*> (resset->get(0)));
    } else {
        throw new DBException(new string("Key not found in key_table"));
    }
    resset->close();
    con->close();
    delete(sql);
    delete(resset);
    delete(con);
    return key;
}

void createKeyInDB(string table) {
    Connection* con = getDefaultDataConnection();
    Statement* stmt = con->createStatement("INSERT INTO key_table  (id, value) VALUES (?, ?)");
    int inc = 50;
    stmt->setParameter(0, DBTYPE_STRING, (void*)table.c_str());
    stmt->setParameter(1, DBTYPE_LONG, &inc);
    stmt->executeUpdate();
    stmt->close();
    delete(stmt);
}

int getKey(string table) {
    Connection* con = getDefaultDataConnection();
    Statement* stmt = con->createStatement("UPDATE key_table set value = value + ? where id = ? ");
    int inc = 50;
    stmt->setParameter(0, DBTYPE_LONG, &inc);
    stmt->setParameter(1, DBTYPE_STRING, (void*)table.c_str());
    int updated = stmt->executeUpdate();
    stmt->close();
    delete(stmt);
    if (updated == 0) {
        createKeyInDB(table);
    }
    return (getKeyFromDB(table) - inc)+1;
}

int getNextKey(string table) {
    map<string, int>::iterator iter = keys.find(table);
    int key;
    if (iter != keys.end()) {
        key = ++iter->second;
    } else {
        key = getKey(table);
        keys.insert(pair<string, int>(table, key));
    }
    return key;
}

