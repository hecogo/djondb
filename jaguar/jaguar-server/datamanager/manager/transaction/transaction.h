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
#include <string.h>

class TransactionEntry;

class TransactionKey {
private:
    int _idEntity;
    int _idAttrib;
    int _entityKey;
    const char* _globalKey;
    int _transactionKeyType; // 0 Entity - 1 Global
public:
    TransactionKey() {

    }
    TransactionKey(const TransactionKey& orig) {

    }
    virtual ~TransactionKey() {

    }

    TransactionKey(int idEntity, int idAttrib, int entityKey) {
        _idEntity = idEntity;
        _idAttrib = idAttrib;
        _entityKey = entityKey;
        _transactionKeyType = 0;
    }

    TransactionKey(const char* globalKey) {
        _globalKey = globalKey;
        _transactionKeyType = 1;
    }
/*
    bool operator==(TransactionKey& comp1, TransactionKey& comp2) {
        return (_transactionKeyType == 0) ? ((comp._entityKey = this->_entityKey) &&
                (comp._idAttrib == this->_idAttrib) && (comp._idEntity == this->_idEntity)) :
            (strcmp(comp._globalKey, this->_globalKey) == 0);
    }

     */
    bool operator==(const TransactionKey& comp) const {
        return (_transactionKeyType == 0) ? ((comp._entityKey == _entityKey) &&
                (comp._idAttrib == _idAttrib) && (comp._idEntity == _idEntity)) :
            (strcmp(comp._globalKey, _globalKey) == 0);
    }

    void setEntityKey(int _entityKey) {
        this->_entityKey = _entityKey;
    }

    int getEntityKey() const {
        return _entityKey;
    }

    void setIdAttrib(int _idAttrib) {
        this->_idAttrib = _idAttrib;
    }

    int getIdAttrib() const {
        return _idAttrib;
    }

    void setIdEntity(int _idEntity) {
        this->_idEntity = _idEntity;
    }

    int getIdEntity() const {
        return _idEntity;
    }
};

struct cmp_key {
    bool operator()(const TransactionKey* a, const TransactionKey* b) {
        if (a->getIdEntity() < b->getIdEntity()) {
            return true;
        } else if (a->getIdEntity() > b->getIdEntity()) {
            return false;
        } else if (a->getIdAttrib() < b->getIdAttrib()) {
            return true;
        } else if (a->getIdAttrib() > b->getIdAttrib()) {
            return false;
        } else if (a->getEntityKey() < b->getEntityKey()) {
            return true;
        } else {
            return false;
        }
    }
};

class Transaction {
public:
    Transaction();
    Transaction(const Transaction& orig);
    virtual ~Transaction();

private:

    int _id;
    int _checkpoints;

    std::vector<TransactionEntry*> _entries;
    std::map<TransactionKey*, TransactionEntry*, cmp_key > _entriesMap;
    TransactionKey* getKey(int idEntity, int idAttrib, int entityKey);
    TransactionKey* getKey(const char* globalName);

public:
    void* getValue(int idEntity, int idAttrib, int entityKey);
    void addEntry(int idEntity, int idAttrib, int entityKey, void* value);
    void commit();
};

#endif	/* _TRANSACTION_H */

