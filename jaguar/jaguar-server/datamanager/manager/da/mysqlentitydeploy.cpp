#include "mysqlentitydeploy.h"
#include "dbjaguar.h"
#include "../attributeMD.h"
#include <iostream>
#include <sstream>

using namespace std;
using namespace dbjaguar;

const char* mysql_createAttribute(SAttribute* attr) {
    stringstream sql;
    sql << attr->name << " ";
    switch (attr->type) {
        case AT_INT:
            sql << "int(11) NULL";
            break;
        case AT_BOOLEAN:
            sql << "BOOLEAN NULL";
            break;
        case AT_DOUBLE:
            sql << "DOUBLE NULL";
            break;
        case AT_VARCHAR:
            sql << "VARCHAR(" << attr->length << ")";
            break;
    }
    return sql.str().c_str();
}

char* mysql_deployEntity(SEntity* entity) {
    stringstream sql;

    sql << "CREATE TABLE  " << entity->tableName << " (" << endl;
    sql << "id int(11) NOT NULL," << endl;
    for (vector<SAttribute*>::iterator iter = entity->attributes.begin();
            iter != entity->attributes.end();
            iter++) {
                sql << mysql_createAttribute(*iter) << ", " << endl;
    }
    sql << "PRIMARY KEY (`id`)" << endl;
    sql << ") ENGINE=MyISAM DEFAULT CHARSET=latin1;" << endl;

    Connection* con = getDefaultDataConnection();
    Statement* stm = con->createStatement(sql.str().c_str());
    stm->executeUpdate();
    stm->close();
    delete(stm);
    con->close();
    delete(con);
    return "0";
}
