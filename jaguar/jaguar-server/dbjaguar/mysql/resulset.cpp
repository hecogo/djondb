#include "mysql.h"
#include <sstream>
#include <stdlib.h>

using namespace dbjaguar;

MYSQL_FIELD** m_res_fields;
int m_res_numfields;

MySQLResultSet::MySQLResultSet(MYSQL_RES* res, const char* query)
{
    m_res = res;
    m_query = query;

    m_res_numfields = mysql_num_fields(res);
    m_res_fields = (MYSQL_FIELD**)malloc(sizeof(MYSQL_FIELD)*m_res_numfields);
    for (int i = 0; i < m_res_numfields; i++)
    {
        MYSQL_FIELD* field = mysql_fetch_field(res);
        m_res_fields[i] = field;
    }
};

bool MySQLResultSet::next() throw (DBException)
{
    m_currentRow = mysql_fetch_row(m_res);
    if (m_currentRow) {
        return true;
    } else {
        return false;
    }
};

bool MySQLResultSet::previous() throw (DBException)
{
    return true;
};

void MySQLResultSet::close() throw (DBException)
{
    while ((m_currentRow = mysql_fetch_row(m_res)));

    mysql_free_result(m_res);
    free(m_res_fields);
}

void* MySQLResultSet::get(int col) throw (DBException)
{
    char* value = (char*)m_currentRow[col];
    MYSQL_FIELD* field = m_res_fields[col];
    switch (field->type) {
        case MYSQL_TYPE_BIT: {
            int ivalue = atoi(value);
            bool* bres;
            *bres =(ivalue == 1)? true:false;
            return bres;
        }
        case MYSQL_TYPE_DOUBLE:
        {
            double* dvalue = (double*)malloc(sizeof(double));
            std::stringstream ss(value);
            ss >> *dvalue;
            return dvalue;
        }
        case MYSQL_TYPE_FLOAT:
        {
            float* fvalue = (float*)malloc(sizeof(double));
            std::stringstream ss(value);
            ss >> *fvalue;
            return fvalue;
        }
        case MYSQL_TYPE_INT24:
        case MYSQL_TYPE_TINY:
        {
            int *ivalue = (int*)malloc(sizeof(int));
            *ivalue = atoi(value);
            return ivalue;
        }
        case MYSQL_TYPE_LONG:
        {
            long *lvalue = (long*)malloc(sizeof(int));
            *lvalue = atol(value);
            return lvalue;
        }
        case MYSQL_TYPE_SHORT:
        {
            short int* shValue = (short int*)malloc(sizeof(short int));
            *shValue = (short int)atoi(value);
            return shValue;
        }
        case MYSQL_TYPE_STRING:
        case MYSQL_TYPE_VAR_STRING:
            return new string(m_currentRow[col]);
            break;
        case MYSQL_TYPE_VARCHAR:
            return value;
            break;

        case MYSQL_TYPE_BLOB:
        case MYSQL_TYPE_DATE:
        case MYSQL_TYPE_DATETIME:
        case MYSQL_TYPE_DECIMAL:
        case MYSQL_TYPE_ENUM:
        case MYSQL_TYPE_GEOMETRY:
        case MYSQL_TYPE_LONGLONG:
        case MYSQL_TYPE_LONG_BLOB:
        case MYSQL_TYPE_MEDIUM_BLOB:
        case MYSQL_TYPE_NEWDATE:
        case MYSQL_TYPE_NEWDECIMAL:
        case MYSQL_TYPE_NULL:
        case MYSQL_TYPE_SET:
        case MYSQL_TYPE_TIME:
        case MYSQL_TYPE_TIMESTAMP:
        case MYSQL_TYPE_TINY_BLOB:
        case MYSQL_TYPE_YEAR:
            throw DBException(new string("Not supported"));
    }
    return value;
}

void* MySQLResultSet::get(const char* colname) throw (DBException)
{
    return NULL;
}

