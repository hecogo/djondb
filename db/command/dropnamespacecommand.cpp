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

#include "dropnamespacecommand.h"

#include "bsonoutputstream.h"
#include "dbcontroller.h"

DropnamespaceCommand::DropnamespaceCommand()
    : Command(DROPNAMESPACE)
{
}

DropnamespaceCommand::DropnamespaceCommand(const DropnamespaceCommand& orig)
: Command(DROPNAMESPACE) {
}

DropnamespaceCommand::~DropnamespaceCommand() {
    delete(_namespace);
    delete(_db);
}

void DropnamespaceCommand::execute() {
    const char* ns = _namespace->c_str();
    dbController()->dropNamespace(const_cast<char*>(_db->c_str()), const_cast<char*>(ns));
}

void* DropnamespaceCommand::result() {
    return NULL;
}

void DropnamespaceCommand::writeResult(OutputStream* out) const {
}

void DropnamespaceCommand::setNameSpace(const std::string& ns) {
    _namespace = new std::string(ns);
}

const std::string* DropnamespaceCommand::nameSpace() const {
    return _namespace;
}

void DropnamespaceCommand::setDB(const std::string& db) {
    _db = new std::string(db);
}

const std::string* DropnamespaceCommand::DB() const {
    return _db;
}

