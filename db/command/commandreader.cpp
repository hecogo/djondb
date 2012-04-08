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

#include "commandreader.h"
#include "insertcommand.h"
#include "dropnamespacecommand.h"
#include "updatecommand.h"
#include "findcommand.h"
#include "bsoninputstream.h"
#include "util.h"

CommandReader::CommandReader(InputStream* is)
{
    _stream = is;
}

CommandReader::CommandReader(const CommandReader& orig) {
    this->_stream = orig._stream;
}

CommandReader::~CommandReader()
{
}

InsertCommand* parseInsert(InputStream* is)  {
    InsertCommand* command = new InsertCommand();
    std::string* ns = is->readString();
    command->setNameSpace(*ns);
    std::auto_ptr<BSONInputStream> bsonis(new BSONInputStream(is));
    BSONObj* obj = bsonis->readBSON();
    command->setBSON(*obj);

    delete ns;
    delete obj;
    return command;
}

DropnamespaceCommand* parseDropnamespace(InputStream* is)  {
    DropnamespaceCommand* command = new DropnamespaceCommand();
    std::string* ns = is->readString();
    command->setNameSpace(*ns);

    delete ns;
    return command;
}

UpdateCommand* parseUpdate(InputStream* is)  {
    UpdateCommand* command = new UpdateCommand();
    std::string* ns = is->readString();
    command->setNameSpace(*ns);
    std::auto_ptr<BSONInputStream> bsonis(new BSONInputStream(is));
    BSONObj* obj = bsonis->readBSON();
    command->setBSON(*obj);

    delete ns;
    delete obj;
    return command;
}

FindCommand* parseFind(InputStream* is)  {
    FindCommand* command = new FindCommand();
    std::string* ns = is->readString();
    command->setNameSpace(*ns);
    std::auto_ptr<BSONInputStream> bsonis(new BSONInputStream(is));
    BSONObj* obj = bsonis->readBSON();
    command->setBSON(*obj);

    delete obj;
    delete ns;
    return command;
}

Command* CommandReader::readCommand() {
    if (_stream->isClosed()) {
        return NULL;
    }
	// at this moment no check has been made, but the version will
	// allow to control that the sender has the same version of the
	// server
	Logger* log = getLogger(NULL);
	if (log->isDebug()) log->debug("readCommand: reading version");
	std::string* version = _stream->readString();
	if (log->isDebug()) log->debug("readCommand: version %s", version->c_str());

    COMMANDTYPE type = static_cast<COMMANDTYPE>(_stream->readInt());

	 if (log->isDebug()) log->debug("readCommand: type %d", type);
    Command* cmd = NULL;
    switch (type) {
        case INSERT: // Insert
            cmd = parseInsert(_stream);
            break;
        case UPDATE: // Update
            cmd = parseUpdate(_stream);
            break;
        case FIND:
            cmd = parseFind(_stream);
            break;
        case DROPNAMESPACE:
            cmd = parseDropnamespace(_stream);
            break;
        case CLOSECONNECTION: // Insert
            cmd = new CloseCommand();
            break;
        default:
            cout << "unknown command type " << type << endl;
            break;
    }
    assert(cmd != NULL);
	 delete log;
    return cmd;
}

