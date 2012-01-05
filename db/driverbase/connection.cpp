#include "connection.h"

#include "networkinputstream.h"
#include "networkoutputstream.h"
#include "commandwriter.h"
#include "insertcommand.h"
#include "findbykeycommand.h"
#include "updatecommand.h"
#include "bsoninputstream.h"
#include "connectionmanager.h"
#include "util.h"

using namespace djondb;

Connection::Connection(std::string host)
{
    _host = host;
    _inputStream = NULL;
    _outputStream = NULL;
    _commandWriter = NULL;
    _open = false;
}

Connection::Connection(const Connection& orig) {
    this->_host = orig._host;
    this->_inputStream = orig._inputStream;
    this->_open =  orig._open;
    this->_outputStream = orig._outputStream;
    this->_commandWriter = orig._commandWriter;
}

Connection::~Connection()
{
    internalClose();
}

bool Connection::open() {
    _outputStream = new NetworkOutputStream();
    int socket = _outputStream->open(_host.c_str(), 1243);
    if (socket > 0) {
        _inputStream = new NetworkInputStream(socket);
        _open = true;
        _commandWriter = new CommandWriter(_outputStream);
        return true;
    } else {
        delete _outputStream;
        return false;
    }
}

void Connection::close() {
    ConnectionManager::releaseConnection(this);
    _open = false;
}

void Connection::internalClose() {
    if (_open) {
        _inputStream->closeStream();
        _outputStream->closeStream();
        if (_inputStream)   {
            delete (_inputStream);
            _inputStream = NULL;
        }
        if (_outputStream)  {
            delete (_outputStream);
            _outputStream = NULL;
        }
        if (_commandWriter) {
            delete (_commandWriter);
            _commandWriter = NULL;
        }
        _open = false;
    }
}

bool Connection::insert(const std::string& ns, const std::string& json) {
	Logger* log = getLogger(NULL);
	if (log->isDebug()) log->debug("insert command. ns: %s, json: %s", ns.c_str(), json.c_str());
    BSONObj* obj = BSONParser::parse(json);
    bool result = insert(ns, *obj);
    delete obj;
	 delete log;
    return result;
}

bool Connection::insert(const std::string& ns, const BSONObj& bson) {
    InsertCommand cmd;
    cmd.setBSON(bson);
    cmd.setNameSpace(ns);
    _commandWriter->writeCommand(&cmd);
    return true;
}

bool Connection::update(const std::string& ns, const std::string& json) {
    BSONObj* obj = BSONParser::parse(json);
    bool result = update(ns, *obj);
    delete obj;
    return result;
}

bool Connection::update(const std::string& ns, const BSONObj& obj) {
    UpdateCommand cmd;
    cmd.setBSON(obj);
    cmd.setNameSpace(ns);

    _commandWriter->writeCommand(&cmd);

    return true;
}

BSONObj* Connection::findByKey(const std::string& ns, const std::string& id) {
    BSONObj filter;
    filter.add("_id", id);

    FindByKeyCommand cmd;
    cmd.setBSON(filter);
    cmd.setNameSpace(ns);
    _commandWriter->writeCommand(&cmd);

    int results = _inputStream->readInt();
    BSONObj* res = NULL;
    if (results > 0) {
        BSONInputStream is(_inputStream);
        res = is.readBSON();
    }
    return res;
}

bool Connection::isOpen() const {
    return _open;
}

std::string Connection::host() const {
    return _host;
}
