#include "transactionentry.h"
#include <stdlib.h>

TransactionEntry::TransactionEntry() {

}

TransactionEntry::TransactionEntry(const TransactionEntry& orig) {

}

TransactionEntry::~TransactionEntry() {
    free(_value);
}

void TransactionEntry::setValue(void* _value) {
    this->_value = _value;
}

void* TransactionEntry::getValue() const {
    return _value;
}

void TransactionEntry::setIdAttribute(int _idAttribute) {
    this->_idAttribute = _idAttribute;
}

int TransactionEntry::setIdAttribute() const {
    return _idAttribute;
}

void TransactionEntry::setIdEntity(int _idEntity) {
    this->_idEntity = _idEntity;
}

int TransactionEntry::setIdEntity() const {
    return _idEntity;
}

void TransactionEntry::setId(int _id) {
    this->_id = _id;
}

int TransactionEntry::setId() const {
    return _id;
}

void TransactionEntry::setIdEntityKey(int _idEntityKey) {
    this->_idEntityKey = _idEntityKey;
}

int TransactionEntry::getIdEntityKey() const {
    return _idEntityKey;
}

