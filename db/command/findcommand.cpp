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
	if (_namespace != NULL) delete _namespace;
	if (_db != NULL) delete _db;

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

	_result = dbController()->find(const_cast<char*>(DB()->c_str()), const_cast<char*>(nameSpace()->c_str()), *bson());
	
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

void FindCommand::setDB(const std::string& db) {
    _db = new std::string(db);
}

const std::string* FindCommand::DB() const {
    return _db;
}

