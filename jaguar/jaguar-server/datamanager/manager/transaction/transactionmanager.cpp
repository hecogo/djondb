/* 
 * File:   TransactionManager.cpp
 * Author: cross
 * 
 * Created on May 20, 2010, 1:54 PM
 */

#include "transactionmanager.h"
#include "transaction.h"

TransactionManager::TransactionManager() {
}

TransactionManager::TransactionManager(const TransactionManager& orig) {
}

TransactionManager::~TransactionManager() {
}

Transaction* TransactionManager::startTransaction() {
    Transaction* transaction = new Transaction();
    return transaction;
}