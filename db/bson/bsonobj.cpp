#include "bsonobj.h"
#include "util.h"

#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

BSONContent::~BSONContent() {
    /*
    switch (_type) {
        case BSON:
            delete _element;
            break;
        case PTRCHAR:
            break;
        default:
            break;
    }
    */
}

BSONObj::BSONObj()
{
    //ctor
}

BSONObj::~BSONObj()
{
    for (std::map<char*, BSONContent*>::const_iterator i = _elements.begin(); i != _elements.end(); i++) {
        BSONContent* cont = i->second;
        delete(cont);
    }
    //dtor
}

/*
void BSONObj::add(char* key, void* val) {
    BSONCONTENT_FILL(key, PTR, val);
}
*/

void BSONObj::add(char* key, int val) {
    BSONCONTENT_FILL(key, INT_TYPE, &val);
}

void BSONObj::add(char* key, double val) {
    BSONCONTENT_FILL(key, DOUBLE_TYPE, &val);
}

void BSONObj::add(char* key, long val) {
    BSONCONTENT_FILL(key, LONG_TYPE, &val);
}

void BSONObj::add(char* key, char* val) {
    BSONCONTENT_FILL(key, PTRCHAR_TYPE, val);
}

void BSONObj::add(char* key, std::string val) {
    BSONCONTENT_FILL(key, STRING_TYPE, &val);
}

void BSONObj::add(char* key, BSONObj* val) {
    BSONCONTENT_FILL(key, BSON_TYPE, val);
}

char* BSONObj::toChar() const {
    std::stringstream ss;
    ss << "{ ";
    bool first = true;
    for (std::map<char*, BSONContent*>::const_iterator i = _elements.begin(); i != _elements.end(); i++) {
        if (!first) {
            ss << ",";
        }
        first = false;
        BSONContent* content = i->second;
        char* key = i->first;
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

int* BSONObj::getInt(char* key) const {
    std::map<char*, BSONContent*>::const_iterator it = _elements.find(key);
    if (it != _elements.end()) {
        int* res = (int*)it->second;
        return res;
    } else {
        return NULL;
    }
}

double* BSONObj::getDouble(char* key) const {
    std::map<char*, BSONContent*>::const_iterator it = _elements.find(key);
    if (it != _elements.end()) {
        double* res = (double*)it->second;
        return res;
    } else {
        return NULL;
    }
}

long* BSONObj::getLong(char* key) const {
    std::map<char*, BSONContent*>::const_iterator it = _elements.find(key);
    if (it != _elements.end()) {
        long* res = (long*)it->second;
        return res;
    } else {
        return NULL;
    }
}

char* BSONObj::getChars(char* key) const {
    std::map<char*, BSONContent*>::const_iterator it = _elements.find(key);
    if (it != _elements.end()) {
        char* res = (char*)it->second;
        return res;
    } else {
        return NULL;
    }
}

std::string* BSONObj::getString(char* key) const {
    std::map<char*, BSONContent*>::const_iterator it = _elements.find(key);
    if (it != _elements.end()) {
        std::string* res = (std::string*)it->second;
        return res;
    } else {
        return NULL;
    }
}

BSONObj* BSONObj::getBSON(char* key) const {
    std::map<char*, BSONContent*>::const_iterator it = _elements.find(key);
    if (it != _elements.end()) {
        BSONObj* res = (BSONObj*)it->second;
        return res;
    } else {
        return NULL;
    }
}

std::map<char*, BSONContent* >::const_iterator BSONObj::begin() const {
    return _elements.begin();
}

std::map<char*, BSONContent* >::const_iterator BSONObj::end() const {
    return _elements.end();
}

int BSONObj::length() const {
    return _elements.size();
}
