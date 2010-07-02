/* 
 * File:   Transaction.cpp
 * Author: cross
 * 
 * Created on May 20, 2010, 1:58 PM
 */

#include <iosfwd>


#include "transaction.h"
#include "transactionentry.h"
#include "../../datamanager.h"
#include "../da/entityda.h"

#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>

Transaction::Transaction() {
}

Transaction::Transaction(const Transaction& orig) {
}

Transaction::~Transaction() {
    std::map<TransactionKey*, TransactionEntry*, cmp_key >::iterator iter = _entriesMap.begin();
    while (iter != _entriesMap.end()) {
        TransactionKey* key = iter->first;
        TransactionEntry* entry = iter->second;
        delete(key);
        delete(entry);
        iter++;
    }
}

TransactionKey* Transaction::getKey(int idEntity, int idAttrib, int entityKey) {
    TransactionKey* key = new TransactionKey(idEntity, idAttrib, entityKey);
    return key;
}

TransactionKey* Transaction::getKey(const char* globalName) {
    TransactionKey* key = new TransactionKey(globalName);
    return key;
}

void* Transaction::getValue(int idEntity, int idAttrib, int entityKey) {
    TransactionKey* key = getKey(idEntity, idAttrib, entityKey);

    std::map< TransactionKey*, TransactionEntry* >::iterator iter = _entriesMap.find(key);

    delete(key);
    // not found
    if (iter == _entriesMap.end()) {
        return NULL;
    } else {
        TransactionEntry* entry = iter->second;
        return entry->getValue();
    }
}

void Transaction::addEntry(int idEntity, int idAttrib, int entityKey, void* value) {
    TransactionEntry* entry = new TransactionEntry();
    entry->setIdEntity(idEntity);
    entry->setIdAttribute(idAttrib);
    entry->setIdEntityKey(entityKey);
    entry->setValue(value);

    _entries.push_back(entry);
    TransactionKey* key = getKey(idEntity, idAttrib, entityKey);
    std::map<TransactionKey*, TransactionEntry*, cmp_key >::iterator iter = _entriesMap.find(key);
    if (iter != _entriesMap.end()) {
        _entriesMap.erase(iter);
    }
    _entriesMap.insert(std::pair<TransactionKey*, TransactionEntry*>(key, entry));
}

void Transaction::commit() {
    int lastIdEntity = 0;
    int lastKey = 0;
    std::vector<int> idAttributes;
    std::vector<void*> values;
    for (std::map<TransactionKey*, TransactionEntry*>::iterator iter = _entriesMap.begin();
            iter != _entriesMap.end();
            iter++) {
        TransactionKey* key = iter->first;
        TransactionEntry* entry = iter->second;
        int currentIdEntity = entry->getIdEntity();
        int currentKey = entry->getIdEntityKey();

        if ((currentIdEntity != lastIdEntity)
                && (lastKey != currentKey)) {
            // New entity values
            if (lastIdEntity != 0) {
                createEntity(lastIdEntity, lastKey, idAttributes, values);
                values.clear();
                idAttributes.clear();
            }
        }
        idAttributes.push_back(entry->getIdAttribute());
        values.push_back(entry->getValue());
        lastIdEntity = currentIdEntity;
        lastKey = currentKey;
    };

    if (lastIdEntity > 0) {
        createEntity(lastIdEntity, lastKey, idAttributes, values);
    }
    _entries.clear();
    _entriesMap.clear();
}