// =====================================================================================
//  Filename:  transaction.cpp
// 
//  Description:  Contains the implementation of the transaction class
// 
//  Version:  1.0
//  Created:  03/12/2012 08:54:24 PM
//  Revision:  none
//  Compiler:  gcc
// 
//  Author:  Juan Pablo Crossley (crossleyjuan@gmail.com), 
// 
// License:
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
// =====================================================================================

#include "transaction.h"
#include "command.h"
#include "insertcommand.h"
#include "updatecommand.h"
#include "findcommand.h"
#include "db.h"

Transaction::Transaction(bool longterm) {
	_longterm = longterm;
}

Transaction::Transaction(const Transaction& orig) {
	this->_longterm = _longterm;

	for (std::map<std::string, Command*>::const_iterator i = orig._commands.begin(); i != orig._commands.end(); i++) {
		Command* cmd = i->second;
		this->insertCommand(i->first, cmd);
	}
}

Transaction::~Transaction() {
	for (std::map<std::string, Command*>::const_iterator i = _commands.begin(); i != _commands.end(); i++) {
		delete(i->second);
	}

	_commands.clear();
}

Command* Transaction::copyCommand(Command* cmd) {
	Command* cpy = NULL;
	switch (cmd->commandType()) {
		case INSERT:
			cpy = new InsertCommand(*((InsertCommand*)cmd));
			break;
		case UPDATE:
			cpy = new UpdateCommand(*((UpdateCommand*)cmd));
			break;
		case FIND:
			cpy = new FindCommand(*((FindCommand*)cmd));
			break;
		case CLOSECONNECTION:
			cpy = new CloseCommand(*((CloseCommand*)cmd));
			break;
		default:
			throw std::string("Command type unkwon: %d", cmd->commandType());
			break;
	}
	return cpy;
}

void Transaction::insertCommand(std::string ns, Command* cmd) {
	_commands.insert(pair<std::string, Command*>(ns, copyCommand(cmd)));
}

std::map<std::string, Command*> Transaction::commands() const {
	return _commands;
}
