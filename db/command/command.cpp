#include "command.h"
#include "bson.h"

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
    delete(_bson);
}

COMMANDTYPE Command::commandType() const
{
    return _commandType;
}

void InsertCommand::execute() {
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
