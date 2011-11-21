#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <map>
#include <string>

namespace djondb {
    class Connection;

    struct ConnectionReference {
        Connection* _connection;
        int _references;
    };

    class ConnectionManager
    {
        public:
            /** Default constructor */
            ConnectionManager();
            /** Default destructor */
            virtual ~ConnectionManager();

            static Connection* getConnection(std::string host);

            static void releaseConnection(Connection* conn);

        protected:
        private:
            static std::map<std::string, struct ConnectionReference> _connections;
    };
}

#endif // CONNECTIONMANAGER_H
