#include "findbykeycommand.h"

#include "bsonoutputstream.h"
#include "dbcontroller.h"
#include "outputstream.h"

FindByKeyCommand::FindByKeyCommand()
: Command(FINDBYKEY)
{
    //ctor
}

FindByKeyCommand::~FindByKeyCommand()
{
}

FindByKeyCommand::FindByKeyCommand(const FindByKeyCommand& other)
:Command(FINDBYKEY)
{
}

void FindByKeyCommand::execute() {
    _bsonResult = dbController()->findFirst(const_cast<char*>(nameSpace().c_str()), bson());
}

void* FindByKeyCommand::result() {
    return _bsonResult;
}

void FindByKeyCommand::writeResult(OutputStream* out) const {
    if (_bsonResult != NULL) {
        out->writeInt(1);
        BSONOutputStream* bsonout = new BSONOutputStream(out);
        bsonout->writeBSON(*_bsonResult);
        delete bsonout;
    } else {
        out->writeInt(0);
    }
}

void FindByKeyCommand::setNameSpace(std::string ns) {
    _namespace = ns;
}

std::string FindByKeyCommand::nameSpace() {
    return _namespace;
}

void FindByKeyCommand::setBSON(const BSONObj bson) {
    _bson = new BSONObj(bson);
}

BSONObj* FindByKeyCommand::bson() const {
    return _bson;
}
