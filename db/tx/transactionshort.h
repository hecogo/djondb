/*
 * =====================================================================================
 *
 *       Filename:  transactionshot.h
 *
 *    Description:  Definition of the short term transaction class
 *
 *        Version:  1.0
 *        Created:  04/11/2012 09:23:35 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Juan Pablo Crossley (crossleyjuan@gmail.com), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef TRANSACTIONSHORT_H_INCLUDED
#define TRANSACTIONSHORT_H_INCLUDED

#include "transaction.h"

class TransactionShort: public Transaction {
	public:
		TransactionShort();
		TransactionShort(const TransactionShort& orig);
		virtual ~TransactionShort();

		virtual void insert(InsertCommand* cmd);
		virtual bool update(UpdateCommand* cmd);
		virtual std::vector<BSONObj*> find(FindCommand* cmd);

		virtual std::map<std::string, Command*> commit();
};

#endif // TRANSACTIONSHORT_H_INCLUDED


