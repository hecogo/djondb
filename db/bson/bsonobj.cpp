#include "bsonobj.h"
#include "util.h"

#include "bsonparser.h"

#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

BSONContent::~BSONContent() {
    if (!_element) {
        return;
    }
    switch (_type) {
        case STRING_TYPE:
            delete ((string*)_element);
            break;
        case PTRCHAR_TYPE:
            free (_element);
            break;
        case INT_TYPE:
            delete ((int*)_element);
            break;
        case LONG_TYPE:
            delete ((long*)_element);
            break;
        case DOUBLE_TYPE:
            delete ((double*)_element);
            break;
        default:
            break;
    }
    _element = 0;
}

BSONContent::BSONContent(const BSONContent& orig) {
    this->_type = orig._type;
    int len = 0;
    int* internalInt;
    long* internalLong;
    double* internalDouble;
    int i;
    long l;
    double d;
    switch (this->_type) {
        case STRING_TYPE:
            this->_element = new std::string(*(std::string*)orig._element);
            break;
        case PTRCHAR_TYPE:
            len = strlen((char*)orig._element);
            this->_element = malloc(len+1);
            memset(this->_element, 0, len + 1);
            memcpy(this->_element, orig._element, len);
            break;
        case INT_TYPE:
            i = *((int*)orig._element);
            internalInt = new int();
            *internalInt = i;
            this->_element = internalInt;
            break;
        case LONG_TYPE:
            l = *((long*)orig._element);
            internalLong = new long();
            *internalLong = l;
            this->_element = internalLong;
            break;
        case DOUBLE_TYPE:
            d = *((double*)orig._element);
            internalDouble = new double();
            *internalDouble = d;
            this->_element = internalDouble;
            break;
        default:
            break;
    }
}

BSONObj::BSONObj()
{
}

BSONObj::~BSONObj()
{
    for (std::map<t_keytype, BSONContent*>::const_iterator i = _elements.begin(); i != _elements.end(); i++) {
        BSONContent* cont = i->second;
        delete(cont);
    }
    _elements.clear();
}

/*
void BSONObj::add(t_keytype key, void* val) {
    BSONCONTENT_FILL(key, PTR, val);
}
*/

void BSONObj::add(t_keytype key, int val) {
    int* internalValue = new int();
    *internalValue = val;
    BSONCONTENT_FILL(key, INT_TYPE, internalValue);
}

void BSONObj::add(t_keytype key, double val) {
    double* internalValue = new double();
    *internalValue = val;
    BSONCONTENT_FILL(key, DOUBLE_TYPE, internalValue);
}

void BSONObj::add(t_keytype key, long val) {
    long* internalValue = new long();
    *internalValue = val;
    BSONCONTENT_FILL(key, LONG_TYPE, internalValue);
}

void BSONObj::add(t_keytype key, char* val) {
    char* internalValue = (char*)malloc(strlen(val) + 1);
    memset(internalValue, 0, strlen(val) + 1);
    strcpy(internalValue, val);
    BSONCONTENT_FILL(key, PTRCHAR_TYPE, internalValue);
}

void BSONObj::add(t_keytype key, std::string val) {
    std::string* internalValue = new std::string(val);
    BSONCONTENT_FILL(key, STRING_TYPE, internalValue);
}

void BSONObj::add(t_keytype key, BSONObj val) {
    BSONObj* internalValue = new BSONObj(val);
    BSONCONTENT_FILL(key, BSON_TYPE, internalValue);
}

char* BSONObj::toChar() const {
    std::stringstream ss;
    ss << "{ ";
    bool first = true;
    for (std::map<t_keytype, BSONContent* >::const_iterator i = _elements.begin(); i != _elements.end(); i++) {
        if (!first) {
            ss << ",";
        }
        first = false;
        BSONContent* content = i->second;
        t_keytype key = i->first;
        ss << key << ":";
        switch (content->_type)  {
            case BSON_TYPE:
                ss << ((BSONObj*)content->_element)->toChar();
                break;
            case INT_TYPE:
                ss << "'" << *((int*)content->_element) << "'";
                break;
            case LONG_TYPE:
                ss << "'" << *((long*)content->_element) << "'";
                break;
            case DOUBLE_TYPE:
                ss << "'" << *((double*)content->_element) << "'";
                break;
            case PTRCHAR_TYPE:
                ss << "'" << (char*)content->_element << "'";
                break;
            case STRING_TYPE:
                ss << "'" << ((std::string*)content->_element)->c_str() << "'";
                break;
        }
    }
    ss << "} ";
    std::string s = ss.str();
    const char* temp = s.c_str();
    int len = s.length();
    char* res = (char*)malloc(len +1);
    memset(res, 0, len + 1);
    memcpy(res, temp, len);
    return res;
}

int* BSONObj::getInt(t_keytype key) const {
    SEARCHBSON(key, INT_TYPE);
    if (content != NULL) {
        int* res = (int*)content->_element;
        return res;
    } else {
        return NULL;
    }
}

double* BSONObj::getDouble(t_keytype key) const {
    SEARCHBSON(key, DOUBLE_TYPE);
    if (content != NULL) {
        double* res = (double*)content->_element;
        return res;
    } else {
        return NULL;
    }
}

long* BSONObj::getLong(t_keytype key) const {
    SEARCHBSON(key, LONG_TYPE);
    if (content != NULL) {
        long* res = (long*)content->_element;
        return res;
    } else {
        return NULL;
    }
}

char* BSONObj::getChars(t_keytype key) const {
    SEARCHBSON(key, PTRCHAR_TYPE);
    if (content != NULL) {
        char* res = (char*)content->_element;
        return res;
    } else {
        return NULL;
    }
}

std::string* BSONObj::getString(t_keytype key) const {
    BSONContent* content = NULL;
//    SEARCHBSON(key, STRING_TYPE);
    for (std::map<t_keytype, BSONContent* >::const_iterator it = _elements.begin(); it != _elements.end(); it++) {
        t_keytype itKey = it->first;
        if (itKey.compare(key) == 0) {
            content = it->second;
            if (content->_type != STRING_TYPE) {
               throw "The type does not match";
            }
            break;
        }
    }
    if (content != NULL) {
        std::string* res = (std::string*)content->_element;
        return res;
    } else {
        return NULL;
    }
}

BSONObj* BSONObj::getBSON(t_keytype key) const {
    SEARCHBSON(key, BSON_TYPE);
    if (content != NULL) {
        BSONObj* res = (BSONObj*)content->_element;
        return res;
    } else {
        return NULL;
    }
}

std::map<t_keytype, BSONContent* >::const_iterator BSONObj::begin() const {
    return _elements.begin();
}

std::map<t_keytype, BSONContent* >::const_iterator BSONObj::end() const {
    return _elements.end();
}

int BSONObj::length() const {
    return _elements.size();
}

bool BSONObj::has(t_keytype key) {
    for (std::map<t_keytype, BSONContent* >::const_iterator it = _elements.begin(); it != _elements.end(); it++) {
        t_keytype itKey = it->first;
        if (itKey.compare(key) == 0) {
            return true;
        }
    }
    return false;
}

BSONObj::BSONObj(const BSONObj& orig) {
    for (std::map<t_keytype, BSONContent* >::const_iterator i = orig._elements.begin(); i != orig._elements.end(); i++) {
        t_keytype key = i->first;
        BSONContent* origContent = i->second;
        BSONContent* content = new BSONContent(*origContent);

        this->_elements.insert(pair<t_keytype, BSONContent* >(i->first, content));
    }
}
