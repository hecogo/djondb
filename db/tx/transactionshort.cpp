/*
 * =====================================================================================
 *
 *       Filename:  transactionshort.cpp
 *
 *    Description:  Short term transaction implementation
 *
 *        Version:  1.0
 *        Created:  04/11/2012 09:24:48 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Juan Pablo Crossley (crossleyjuan@gmail.com), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>

TransactionShort::TransactionShort():
	Transaction(false) {

	};

TransactionShort::TransactionShort(const TransactionShort& orig) {
	this->_longterm = orig._longterm;
}

~TransactionShort::TransactionShort() {

}

void TransactionShort::insert(InsertCommand* cmd) {
	insertCommand(cmd);
}

bool TransactionShort::update(UpdateCommand* cmd) {
	insertCommand(cmd);
}

std::vector<BSONObj*> TransactionShort::find(FindCommand* cmd) {

}

std::map<std::string, Command*> TransactionShort::commit() {

}
};


