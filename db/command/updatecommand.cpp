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

#include "updatecommand.h"

#include "bsonoutputstream.h"
#include "dbcontroller.h"

UpdateCommand::UpdateCommand()
    : Command(UPDATE)
{
}

UpdateCommand::UpdateCommand(const UpdateCommand& orig)
: Command(UPDATE) {
}

UpdateCommand::~UpdateCommand() {
    delete(_namespace);
    delete(_bson);
}

void UpdateCommand::execute() {
    const char* ns = _namespace->c_str();
    dbController()->update(const_cast<char*>(ns), _bson);
}

void* UpdateCommand::result() {
    return NULL;
}

void UpdateCommand::writeResult(OutputStream* out) const {
}

void UpdateCommand::setNameSpace(const std::string ns) {
    _namespace = new std::string(ns);
}

const std::string* UpdateCommand::nameSpace() const {
    return _namespace;
}

void UpdateCommand::setBSON(const BSONObj bson) {
    _bson = new BSONObj(bson);
}

BSONObj* UpdateCommand::bson() const {
    return _bson;
}
