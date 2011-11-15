#include "updatecommand.h"

#include "bsonoutputstream.h"

UpdateCommand::UpdateCommand()
    : Command(UPDATE)
{
}

UpdateCommand::UpdateCommand(const UpdateCommand& orig)
: Command(UPDATE) {
}

UpdateCommand::~UpdateCommand() {
    delete(_namespace);
    delete(_bson);
}

void UpdateCommand::execute() {
    const char* ns = _namespace->c_str();
    dbController()->update(const_cast<char*>(ns), _bson);
}

void* UpdateCommand::result() {
    return NULL;
}

void UpdateCommand::writeResult(OutputStream* out) const {
}

void UpdateCommand::setNameSpace(const std::string ns) {
    _namespace = new std::string(ns);
}

const std::string* UpdateCommand::nameSpace() const {
    return _namespace;
}

void UpdateCommand::setBSON(const BSONObj bson) {
    _bson = new BSONObj(bson);
}

BSONObj* UpdateCommand::bson() const {
    return _bson;
}
