/*
 * =====================================================================================
 *
 *       Filename:  transactionlog.h
 *
 *    Description:  Long term transaction definition
 *
 *        Version:  1.0
 *        Created:  04/11/2012 09:21:17 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Juan Pablo Crossley (crossleyjuan@gmail.com), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef TRANSACTIONLONG_H_INCLUDED
#define TRANSACTIONLONG_H_INCLUDED

#include "transaction.h"

class TransactionLong: public Transaction {
	public:
		TransactionLong();
		TransactionLong(const TransactionLong& orig);
		virtual ~TransactionLong();

		virtual void insert(InsertCommand* cmd);
		virtual bool update(UpdateCommand* cmd);
		virtual std::vector<BSONObj*> find(FindCommand* cmd);

		virtual std::map<std::string, Command*> commit();
};

#endif // TRANSACTIONLONG_H_INCLUDED
