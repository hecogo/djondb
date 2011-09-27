#include "command.h"

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
}

COMMANDTYPE Command::commandType() const
{
    return _commandType;
}
