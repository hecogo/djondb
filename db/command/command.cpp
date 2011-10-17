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

COMMANDTYPE Command::commandType() const
{
    return _commandType;
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

