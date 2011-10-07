#include "bsonobj.h"
#include "util.h"

#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

BSONContent::~BSONContent() {
    switch (_type) {
        case STRING_TYPE:
            delete ((string*)_element);
            break;
        case PTRCHAR_TYPE:
            free ((char*)_element);
            break;
        default:
            break;
    }
}

BSONObj::BSONObj()
{
    //ctor
}

BSONObj::~BSONObj()
{
    for (std::map<t_keytype, BSONContent*>::const_iterator i = _elements.begin(); i != _elements.end(); i++) {
        BSONContent* cont = i->second;
        delete(cont);
    }
    _elements.clear();
    //dtor
}

/*
void BSONObj::add(t_keytype key, void* val) {
    BSONCONTENT_FILL(key, PTR, val);
}
*/

void BSONObj::add(t_keytype key, int val) {
    BSONCONTENT_FILL(key, INT_TYPE, &val);
}

void BSONObj::add(t_keytype key, double val) {
    BSONCONTENT_FILL(key, DOUBLE_TYPE, &val);
}

void BSONObj::add(t_keytype key, long val) {
    BSONCONTENT_FILL(key, LONG_TYPE, &val);
}

void BSONObj::add(t_keytype key, char* val) {
    BSONCONTENT_FILL(key, PTRCHAR_TYPE, val);
}

void BSONObj::add(t_keytype key, std::string* val) {
    BSONCONTENT_FILL(key, STRING_TYPE, val);
}

void BSONObj::add(t_keytype key, BSONObj* val) {
    BSONCONTENT_FILL(key, BSON_TYPE, val);
}

char* BSONObj::toChar() const {
    std::stringstream ss;
    ss << "{ ";
    bool first = true;
    for (std::map<t_keytype, BSONContent*>::const_iterator i = _elements.begin(); i != _elements.end(); i++) {
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
    BSONContent* content = NULL;
    SEARCHBSON(key, INT_TYPE);
    if (content != NULL) {
        int* res = (int*)content->_element;
        return res;
    } else {
        return NULL;
    }
}

double* BSONObj::getDouble(t_keytype key) const {
    BSONContent* content = NULL;
    SEARCHBSON(key, DOUBLE_TYPE);
    if (content != NULL) {
        double* res = (double*)content->_element;
        return res;
    } else {
        return NULL;
    }
}

long* BSONObj::getLong(t_keytype key) const {
    BSONContent* content = NULL;
    SEARCHBSON(key, LONG_TYPE);
    if (content != NULL) {
        long* res = (long*)content->_element;
        return res;
    } else {
        return NULL;
    }
}

char* BSONObj::getChars(t_keytype key) const {
    BSONContent* content = NULL;
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
    for (std::map<t_keytype, BSONContent*>::const_iterator it = _elements.begin(); it != _elements.end(); it++) {
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
    BSONContent* content = NULL;
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
    for (std::map<t_keytype, BSONContent*>::const_iterator it = _elements.begin(); it != _elements.end(); it++) {
        t_keytype itKey = it->first;
        if (itKey.compare(key) == 0) {
            return true;
        }
    }
    return false;
}
