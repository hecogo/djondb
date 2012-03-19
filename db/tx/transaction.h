// =====================================================================================
//  Filename:  transaction.h
// 
//  Description:  Contains the definition of the transaction class
// 
//  Version:  1.0
//  Created:  03/12/2012 08:49:22 PM
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

#ifndef TRANSACTION_INCLUDED_H
#define TRANSACTION_INCLUDED_H

class Command;
class InsertCommand;
class FindCommand;
class UpdateCommand;
class DBController;
class BSONObj;

class FileOutputStream;
#include <map>
#include <vector>
#include <string>

class Transaction {
	public:
		Transaction(DBController* controller, bool longterm);
		Transaction(const Transaction& orig);
		virtual ~Transaction();

		void commitTransaction();
		void dropTransaction();

		void insert(InsertCommand* cmd);
		void update(UpdateCommand* cmd);
		std::vector<BSONObj*> find(FindCommand* cmd);

	private:
		Command* copyCommand(Command* cmd);
		void insertCommand(std::string ns, Command* cmd);

	private:
		std::map<std::string, Command*> _commands;
		bool _longterm;
		DBController* _controller;

		FileOutputStream* _stream;
};

#endif // TRANSACTION_INCLUDED_H

