#include "findcommand.h"

#include "bsonoutputstream.h"
#include "dbcontroller.h"
#include "outputstream.h"
#include "util.h"

FindCommand::FindCommand()
: Command(FIND)
{
	//ctor
}

FindCommand::~FindCommand()
{
	if (_bson != NULL) delete _bson;

	for (std::vector<BSONObj*>::const_iterator i = _result.begin(); i != _result.end(); i++) {
		delete *i;
	}
	
}

FindCommand::FindCommand(const FindCommand& other)
:Command(FIND)
{
}

void FindCommand::execute() {
	Logger* log = getLogger(NULL);
	if (log->isDebug()) log->debug("executing find command on %s", nameSpace()->c_str());

	_result = dbController()->find(const_cast<char*>(nameSpace()->c_str()), *bson());
	
	delete log;
}

void* FindCommand::result() {
	return &_result;
}

void FindCommand::writeResult(OutputStream* out) const {
	Logger* log = getLogger(NULL);
	if (log->isDebug()) log->debug("writing result of find command on %s", nameSpace()->c_str());
	BSONOutputStream* bsonout = new BSONOutputStream(out);
	bsonout->writeBSONArray(_result);
	delete bsonout;
	delete log;
}

void FindCommand::setNameSpace(const std::string& ns) {
	_namespace = new std::string(ns);
}

std::string* FindCommand::nameSpace() const {
	return _namespace;
}

void FindCommand::setBSON(const BSONObj bson) {
	_bson = new BSONObj(bson);
}

BSONObj* FindCommand::bson() const {
	return _bson;
}
