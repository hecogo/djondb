/* 
 * File:   TransactionManager.h
 * Author: cross
 *
 * Created on May 20, 2010, 1:54 PM
 */

#ifndef _TRANSACTIONMANAGER_H
#define	_TRANSACTIONMANAGER_H

class Transaction;

class TransactionManager {
public:
    TransactionManager();
    TransactionManager(const TransactionManager& orig);
    virtual ~TransactionManager();

    Transaction startTransaction();
private:

};

#endif	/* _TRANSACTIONMANAGER_H */

