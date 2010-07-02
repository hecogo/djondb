#ifndef _DBJAGUAR_H
#define _DBJAGUAR_H

#include <exception>
#include <string>
#include <mysql/mysql.h>

using namespace std;

// **********************************************************************
// Public functions
int getNextKey(string table);
void getConnectionInfo(const char* connectionDef, string* type, string* server, string* port, string* database);

// **********************************************************************

#define THROWERROR() \
    string* connerror = new string("DBException: "); \
    const char* error = mysql_error(m_mysql); \
    connerror->append(error); \
    throw DBException(connerror);

#define PERSISTENCE_FIELDS \
    private: \
        dbjaguar::PERSISTENCE_STATUS m_DBJaguarPStatus; \
    public: \
        dbjaguar::PERSISTENCE_STATUS getDBJaguarPStatus() { \
            return m_DBJaguarPStatus; \
        } \
        void setDBJaguarPStatus(dbjaguar::PERSISTENCE_STATUS status) { \
            m_DBJaguarPStatus = status; \
        }
#define PERSISTENCE_SAVED_STATUS(obj) \
    obj->getDBJaguarPStatus() == PSTATUS_SAVED
#define SETPERSISTENCE_SAVED_STATUS(obj) \
    obj->setDBJaguarPStatus(PSTATUS_SAVED);
#define PERSISTENCE_NEW_STATUS(obj) \
    obj->getDBJaguarPStatus() == PSTATUS_NEW
#define SETPERSISTENCE_NEW_STATUS(obj) \
    obj->setDBJaguarPStatus(PSTATUS_NEW);
namespace dbjaguar {
    class Connection;
    class ConnectionPool;
    class ResultSet;

    enum DBFIELD_TYPE {
        DBTYPE_TINY, // 	TINYINT field
        DBTYPE_SHORT, // 	SMALLINT field
        DBTYPE_LONG, // 	INTEGER field
        DBTYPE_INT24, // 	MEDIUMINT field
        DBTYPE_LONGLONG, // 	BIGINT field
        DBTYPE_DECIMAL, // 	DECIMAL or NUMERIC field
        DBTYPE_NEWDECIMAL, // 	Precision math DECIMAL or NUMERIC field (MySQL 5.0.3 and up)
        DBTYPE_FLOAT, // 	FLOAT field
        DBTYPE_DOUBLE, // 	DOUBLE or REAL field
        DBTYPE_TIMESTAMP, // 	TIMESTAMP field
        DBTYPE_DATE, // 	DATE field
        DBTYPE_TIME, // 	TIME field
        DBTYPE_DATETIME, // 	DATETIME field
        DBTYPE_YEAR, // 	YEAR field
        DBTYPE_STRING, // 	CHAR field
        DBTYPE_VAR_STRING, //	VARCHAR field
        DBTYPE_BLOB, // 	BLOB or TEXT field (use max_length to determine the maximum length)
        DBTYPE_SET, // 	SET field
        DBTYPE_ENUM, // 	ENUM field
        DBTYPE_NULL, // 	NULL-type field
        DBTYPE_CHAR //
    };

    enum PERSISTENCE_STATUS {
        PSTATUS_NEW,
        PSTATUS_SAVED
    };

    void setLastError(int errorCode, const char* error);

    const char* getLastError();

    int getLastErrorCode();
    
    class DBException : public exception {
    private:
        string* message;
    public:

        DBException(string* _message) {
            message = _message;
        }

        virtual const char* what() const throw () {
            return message->c_str();
        }
    };

    class ConnectionPool {
    private:
        int size; // Defines the size of the connection pool
        void initializeConnectionPool();
    public:
        ConnectionPool();
        // _connectionDef: type;server:port;database
        Connection* getConnection(const char* _connectionDef, const char* username, const char* password) throw (DBException);
    };

    class Statement {
    protected:
        MYSQL* m_mysql;
        const char* m_query;
    public:

        Statement(MYSQL* _mysql, const char* query) {
            m_mysql = _mysql;
            m_query = query;
        };

        virtual ~Statement() {

        };
        virtual int executeUpdate() = 0;
        virtual void setParameter(int paramName, DBFIELD_TYPE type, void* value) = 0;
        virtual void close() = 0;
    };

    class ResultSet {
    public:
        virtual ~ResultSet() {
            
        }
        
        virtual bool next() throw (DBException) {
            return false;
        }

        virtual bool previous() throw (DBException) {
            return false;
        }

        virtual void close() throw (DBException) {
        }

        virtual void* get(int col) throw (DBException) {
            return NULL;
        }

        virtual void* get(const char* colname) throw (DBException) {
            return NULL;
        }

        virtual int getColumnCount() = 0;

        bool operator++(int) {
            return next();
        }

        bool operator--(int) {
            return previous();
        }
    };

    class Connection {
    public:
        virtual ~Connection() {

        }
        
        virtual void open(const char* _connectiondef, const char* username, const char* password) throw (DBException) {
        };

        virtual void close() throw (DBException) {
        };

        virtual ResultSet* executeQuery(const char* query) throw (DBException) {
            return NULL;
        };

        virtual int executeUpdate(const char* query) throw (DBException) {
            return 0;
        };
        virtual Statement* createStatement(const char* query) throw (DBException) = 0;
    };
}

dbjaguar::Connection* getDefaultMDConnection();
dbjaguar::Connection* getDefaultDataConnection();
void destroyPool();

#endif // _DBJAGUAR_H
