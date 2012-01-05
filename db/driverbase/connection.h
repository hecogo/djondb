#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>
#include <vector>
#include "bson.h"

class NetworkOutputStream;
class NetworkInputStream;
class CommandWriter;

namespace djondb {

    class Connection
    {
        public:
            /** Default constructor */
            Connection(std::string host);
            Connection(const Connection& orig);

            /** Default destructor */
            virtual ~Connection();

            bool open();
            void close();
            void internalClose();
            bool isOpen() const;

            bool insert(const std::string& ns, const std::string& json);
            bool insert(const std::string& ns, const BSONObj& obj);
            BSONObj* findByKey(const std::string& ns, const std::string& id);
				std::vector<BSONObj*> find(const std::string& ns, const std::string& filter);
            std::vector<BSONObj*> find(const std::string& ns, const BSONObj& bsonFilter);
            bool update(const std::string& ns, const std::string& json);
            bool update(const std::string& ns, const BSONObj& bson);

            std::string host() const;

        protected:
        private:
            NetworkOutputStream*  _outputStream;
            NetworkInputStream*   _inputStream;
            CommandWriter*        _commandWriter;

            std::string _host;
            bool _open;
    };

}

#endif // CONNECTION_H
