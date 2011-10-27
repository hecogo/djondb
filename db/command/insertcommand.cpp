#include "insertcommand.h"

#include "bsonoutputstream.h"

InsertCommand::InsertCommand()
    : Command(INSERT)
{
}

InsertCommand::InsertCommand(const InsertCommand& orig)
: Command(INSERT) {
}

InsertCommand::~InsertCommand() {
    delete(_namespace);
    delete(_bson);
}

void InsertCommand::execute() {
    const char* ns = _namespace->c_str();
    _bsonResult = dbController()->insert(const_cast<char*>(ns), _bson);
}

void* InsertCommand::result() {
    return _bsonResult;
}

void InsertCommand::writeResult(OutputStream* out) const {
    if (_bsonResult) {
        BSONOutputStream* bsonout = new BSONOutputStream(out);
        bsonout->writeBSON(*_bsonResult);
    }
}

void InsertCommand::setNameSpace(const std::string ns) {
    _namespace = new std::string(ns);
}
const std::string* InsertCommand::nameSpace() const {
    return _namespace;
}

void InsertCommand::setBSON(const BSONObj bson) {
    _bson = new BSONObj(bson);
}

BSONObj* InsertCommand::bson() const {
    return _bson;
}
