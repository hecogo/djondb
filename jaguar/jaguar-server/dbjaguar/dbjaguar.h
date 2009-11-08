#include <exception>
#include <string>

using namespace std;

namespace dbjaguar
{
    class Connection;
    class ConnectionPool;
    class ResultSet;

    class DBException : public exception
    {
    private:
        string* message;
    public:
        DBException(string* _message)
        {
            message = _message;
        }

        virtual const char* what() const throw ()
        {
            return message->c_str();
        }
    };

    class ConnectionPool
    {
    private:
        int size; // Defines the size of the connection pool
        void initializeConnectionPool();
    public:
        ConnectionPool();
        // _connectionDef: type;server:port;database
        Connection* getConnection(const char* _connectionDef, const char* username, const char* password) throw (DBException);
    };

    class ResultSet
    {
    public:
        virtual bool next() throw (DBException) {
            return false;
        }
        virtual bool previous() throw (DBException) { return false; }
        virtual void close() throw (DBException) {}
        virtual void* get(int col) throw (DBException) { return NULL; }
        virtual void* get(const char* colname) throw (DBException) { return NULL; }

        bool operator++(int) {
            return next();
        }

        bool operator--(int) {
            return previous();
        }
    };

    class Connection
    {
    public:
        virtual void open(const char* _connectiondef, const char* username, const char* password) throw (DBException) {};
        virtual void close() throw (DBException) {};
        virtual ResultSet* executeQuery(const char* query) throw (DBException) { return NULL; };
        virtual int executeUpdate(const char* query) throw (DBException) { return 0; };
    };

}
