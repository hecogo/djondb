#include "commandwriter.h"
#include "insertcommand.h"
#include "updatecommand.h"
#include "findcommand.h"
#include "bsonoutputstream.h"
#include <memory>
#include <iostream>

using namespace std;

CommandWriter::CommandWriter(OutputStream* out)
{
    _stream = out;
}

CommandWriter::~CommandWriter()
{
    //dtor
}


CommandWriter::CommandWriter(const CommandWriter& orig) {
    this->_stream = orig._stream;
}

int CommandWriter::writeInsert(InsertCommand* cmd, OutputStream* out)  {
    const std::string* ns = cmd->nameSpace();
    out->writeString(*ns);

    std::auto_ptr<BSONOutputStream> bsonout(new BSONOutputStream(out));
    bsonout->writeBSON(*cmd->bson());

    return 0;
}

int CommandWriter::writeUpdate(UpdateCommand* cmd, OutputStream* out)  {
    const std::string* ns = cmd->nameSpace();
    out->writeString(*ns);

    std::auto_ptr<BSONOutputStream> bsonout(new BSONOutputStream(out));
    bsonout->writeBSON(*cmd->bson());

    return 0;
}

int CommandWriter::writeFind(FindCommand* cmd, OutputStream* out)  {
    std::string* ns = cmd->nameSpace();
    out->writeString(*ns);

    std::auto_ptr<BSONOutputStream> bsonout(new BSONOutputStream(out));
    bsonout->writeBSON(*cmd->bson());

    return 0;
}

int CommandWriter::writeCommand(Command* cmd) {
    std::string version = "1.2.3";
    _stream->writeString(version);
    int type = cmd->commandType();
    _stream->writeInt(type);

    int ret = 0;
    switch (type) {
        case INSERT: // Insert
            ret = writeInsert((InsertCommand*)cmd, _stream);
            break;
        case UPDATE: // Update
            ret = writeUpdate((UpdateCommand*)cmd, _stream);
            break;
        case FIND:
            ret = writeFind((FindCommand*)cmd, _stream);
            break;
        case CLOSECONNECTION: // Nothing to be done
            break;
        default:
            cout << "Unknown type: " << type << endl;
            ret = 1;
            break;
    }
    return ret;
}

