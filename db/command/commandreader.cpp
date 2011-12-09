#include "commandreader.h"
#include "insertcommand.h"
#include "updatecommand.h"
#include "findbykeycommand.h"
#include "bsoninputstream.h"

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

FindByKeyCommand* parseFindByKey(InputStream* is)  {
    FindByKeyCommand* command = new FindByKeyCommand();
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
	std::string* version = _stream->readString();
    COMMANDTYPE type = static_cast<COMMANDTYPE>(_stream->readInt());
    Command* cmd = NULL;
    switch (type) {
        case INSERT: // Insert
            cmd = parseInsert(_stream);
            break;
        case UPDATE: // Update
            cmd = parseUpdate(_stream);
            break;
        case FINDBYKEY:
            cmd = parseFindByKey(_stream);
            break;
        case CLOSECONNECTION: // Insert
            cmd = new CloseCommand();
            break;
        default:
            cout << "unknown command type " << type << endl;
            break;
    }
    assert(cmd != NULL);
    return cmd;
}

