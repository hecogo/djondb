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

class TransactionKey {
private:
    int _idEntity;
    int _idAttrib;
    int _entityKey;
    const char* _globalKey;
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
    }

    TransactionKey(const char* globalKey) {
        _globalKey = globalKey;
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

class Transaction {
public:
    Transaction();
    Transaction(const Transaction& orig);
    virtual ~Transaction();

private:

    int _id;
    int _checkpoints;

    std::vector<TransactionEntry*> _entries;
    std::map<TransactionKey*, TransactionEntry* > _entriesMap;
    TransactionKey* getKey(int idEntity, int idAttrib, int entityKey);
    TransactionKey* getKey(const char* globalName);

public:
    void* getValue(int idEntity, int idAttrib, int entityKey);
    void addEntry(int idEntity, int idAttrib, int entityKey, void* value);
};

#endif	/* _TRANSACTION_H */

