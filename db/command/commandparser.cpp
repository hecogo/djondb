#include "commandparser.h"

#include "command.h"
#include "inputstream.h"
#include "bsoninputstream.h"


InsertCommand* parseInsert(InputStream* is)  {
    InsertCommand* command = new InsertCommand();
    std::string* ns = is->readString();
    command->setNameSpace(ns);

    BSONInputStream* bsonis = new BSONInputStream(is);
    BSONObj* obj = bsonis->readBSON();
    command->setBSON(obj);

    return command;
}

CommandParser::CommandParser()
{
    //ctor
}

CommandParser::~CommandParser()
{
    //dtor
}

Command* CommandParser::parse(InputStream* is) {
    int type = is->readInt();
    Command* cmd = NULL;
    switch (type) {
        case 1: // Insert
            cmd = parseInsert(is);
            break;
        case CLOSECONNECTION: // Insert
            cmd = new CloseCommand();
            break;
        default:
            cout << "Unknown type: " << type << endl;
            break;
    }
    return cmd;
}
