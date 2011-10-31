#include "findbykeycommand.h"

#include "bsonoutputstream.h"

FindByKeyCommand::FindByKeyCommand()
: Command(FINDBYKEY)
{
    //ctor
}

FindByKeyCommand::~FindByKeyCommand()
{
    //dtor
}

FindByKeyCommand::FindByKeyCommand(const FindByKeyCommand& other)
:Command(FINDBYKEY)
{
}

void FindByKeyCommand::execute() {
    _bsonResult = dbController()->findFirst(const_cast<char*>(nameSpace()->c_str()), bson());
}

void* FindByKeyCommand::result() {
    return _bsonResult;
}

void FindByKeyCommand::writeResult(OutputStream* out) const {
    BSONOutputStream* bsonout = new BSONOutputStream(out);
    bsonout->writeBSON(*_bsonResult);
    delete bsonout;
}

void FindByKeyCommand::setNameSpace(const std::string* ns) {
    _namespace = ns;
}
const std::string* FindByKeyCommand::nameSpace() const {
    return _namespace;
}

void FindByKeyCommand::setBSON(BSONObj* bson) {
    _bson = bson;
}

BSONObj* FindByKeyCommand::bson() const {
    return _bson;
}
