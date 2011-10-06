#include "command.h"
#include "bson.h"
#include "bsonoutputstream.h"

Command::Command(COMMANDTYPE commandType)
{
    _commandType = commandType;
}

Command::Command(const Command& orig) {
    this->_commandType = orig._commandType;
}

Command::~Command() {
}

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

COMMANDTYPE Command::commandType() const
{
    return _commandType;
}

void InsertCommand::execute() {
    const char* ns = _namespace->c_str();
    dbController()->insert(const_cast<char*>(ns), _bson);
}

void* InsertCommand::result() {
    return _bson;
}

CloseCommand::CloseCommand()
: Command(CLOSECONNECTION)
{
}

CloseCommand::CloseCommand(const CloseCommand& orig)
: Command(CLOSECONNECTION) {
}

CloseCommand::~CloseCommand() {
}

void CloseCommand::execute() {
}

void InsertCommand::writeResult(OutputStream* out) const {
    BSONOutputStream* bsonout = new BSONOutputStream(out);
    bsonout->writeBSON(*_bson);
}
