/* 
 * File:   Transaction.h
 * Author: cross
 *
 * Created on May 20, 2010, 1:58 PM
 */

#ifndef _TRANSACTION_H
#define	_TRANSACTION_H

#include <vector>
#include <map>

class TransactionEntry;

class Transaction {
public:
    Transaction();
    Transaction(const Transaction& orig);
    virtual ~Transaction();
    void addEntry(char* entName, int id, void* value);

private:

    int _id;
    int _checkpoints;
    
    std::vector<TransactionEntry*> _entries;
    std::map<char*, std::vector<TransactionEntry*> > _entriesMap;
    const char* getKey(char* entityName, int id);
    const char* getKey(char* globalName);
};

#endif	/* _TRANSACTION_H */

