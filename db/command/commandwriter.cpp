// *********************************************************************************************************************
// file:
// author: Juan Pablo Crossley (crossleyjuan@gmail.com)
// created:
// updated:
// license:
// 
// This file is part of the djondb project, for license information please refer to the LICENSE file,
// the application and libraries are provided as-is and free of use under the terms explained in the file LICENSE
// Its authors create this application in order to make the world a better place to live, but you should use it on
// your own risks.
// 
// Also, be adviced that, the GPL license force the committers to ensure this application will be free of use, thus
// if you do any modification you will be required to provide it for free unless you use it for personal use (you may 
// charge yourself if you want), bare in mind that you will be required to provide a copy of the license terms that ensures
// this program will be open sourced and all its derivated work will be too.
// *********************************************************************************************************************

#include "commandwriter.h"
#include "insertcommand.h"
#include "dropnamespacecommand.h"
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

int CommandWriter::writeDropnamespace(DropnamespaceCommand* cmd, OutputStream* out)  {
    const std::string* ns = cmd->nameSpace();
    out->writeString(*ns);

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
        case DROPNAMESPACE:
            ret = writeDropnamespace((DropnamespaceCommand*)cmd, _stream);
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

