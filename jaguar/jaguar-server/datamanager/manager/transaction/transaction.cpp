/* 
 * File:   Transaction.cpp
 * Author: cross
 * 
 * Created on May 20, 2010, 1:58 PM
 */

#include <iosfwd>


#include "transaction.h"

#include <sstream>
#include <iostream>

Transaction::Transaction() {
}

Transaction::Transaction(const Transaction& orig) {
}

Transaction::~Transaction() {
}

const char* Transaction::getKey(char* entityName, int id) {
    std::stringstream ss;
    ss << entityName << id;

    return ss.str().c_str();
}

const char* Transaction::getKey(char* globalName) {
    std::stringstream ss;
    ss << globalName;

    return ss.str().c_str();
}
