// =====================================================================================
//  Filename:  transactionmanager.cpp
// 
//  Description:  This class will control the transactions within the server
// 
//  Version:  1.0
//  Created:  03/12/2012 08:28:14 PM
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

#include "transactionmanager.h"
#include "transaction.h"
#include "util.h"
#include "db.h"

std::map<std::string, Transaction*> TransactionManager::_transactions;
TransactionManager* TransactionManager::_manager;

TransactionManager* TransactionManager::transactionManager() {
	if (_manager == NULL) {
		_manager = new TransactionManager();
	}

	return _manager;
}

TransactionManager::TransactionManager() {

}

TransactionManager::~TransactionManager() {

}

TransactionManager::TransactionManager(const TransactionManager& orig) {

}

Transaction* TransactionManager::beginTransaction(bool longterm) {
	std::string* id = uuid();
	DBController* controller = new DBController();
	controller->initialize("tran" + *id);

	Transaction* tran = new Transaction(controller, longterm);
	_transactions.insert(pair<std::string, Transaction*>(*id, tran));
	delete id;

	return tran;
}

Transaction* TransactionManager::loadTransaction(std::string id) {
	DBController* controller = new DBController();
	controller->initialize("tran" + id);

	Transaction* tran = new Transaction(controller, true);
	_transactions.insert(pair<std::string, Transaction*>(id, tran));

	return tran;
}
