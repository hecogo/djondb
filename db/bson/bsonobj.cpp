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
        case PTRCHAR_TYPE:
            free((char*)_element);
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
    for (std::map<t_keytype, boost::shared_ptr<BSONContent> >::const_iterator i = _elements.begin(); i != _elements.end(); i++) {
        if (!first) {
            ss << ",";
        }
        first = false;
        boost::shared_ptr<BSONContent> content = i->second;
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
    boost::shared_ptr<BSONContent> content;
    SEARCHBSON(key, INT_TYPE);
    if (content != NULL) {
        int* res = (int*)content->_element;
        return res;
    } else {
        return NULL;
    }
}

double* BSONObj::getDouble(t_keytype key) const {
    boost::shared_ptr<BSONContent> content;
    SEARCHBSON(key, DOUBLE_TYPE);
    if (content != NULL) {
        double* res = (double*)content->_element;
        return res;
    } else {
        return NULL;
    }
}

long* BSONObj::getLong(t_keytype key) const {
    boost::shared_ptr<BSONContent> content;
    SEARCHBSON(key, LONG_TYPE);
    if (content != NULL) {
        long* res = (long*)content->_element;
        return res;
    } else {
        return NULL;
    }
}

char* BSONObj::getChars(t_keytype key) const {
    boost::shared_ptr<BSONContent> content;
    SEARCHBSON(key, PTRCHAR_TYPE);
    if (content != NULL) {
        char* res = (char*)content->_element;
        return res;
    } else {
        return NULL;
    }
}

boost::shared_ptr<std::string> BSONObj::getString(t_keytype key) const {
    boost::shared_ptr<BSONContent> content;
//    SEARCHBSON(key, STRING_TYPE);
    for (std::map<t_keytype, boost::shared_ptr<BSONContent> >::const_iterator it = _elements.begin(); it != _elements.end(); it++) {
        t_keytype itKey = it->first;
        if (itKey.compare(key) == 0) {
            content = it->second;
            if (content->_type != STRING_TYPE) {
               throw "The type does not match";
            }
            break;
        }
    }
    boost::shared_ptr<std::string> res;
    if (content != NULL) {
        res = boost::shared_ptr<std::string>((std::string*)content->_element);
    }
    return res;
}

boost::shared_ptr<BSONObj> BSONObj::getBSON(t_keytype key) const {
    boost::shared_ptr<BSONContent> content;
    SEARCHBSON(key, BSON_TYPE);
    boost::shared_ptr<BSONObj> res;
    if (content != NULL) {
        boost::shared_ptr<BSONObj>((BSONObj*)content->_element);
    }
    return res;
}

std::map<t_keytype, boost::shared_ptr<BSONContent> >::const_iterator BSONObj::begin() const {
    return _elements.begin();
}

std::map<t_keytype, boost::shared_ptr<BSONContent> >::const_iterator BSONObj::end() const {
    return _elements.end();
}

int BSONObj::length() const {
    return _elements.size();
}

bool BSONObj::has(t_keytype key) {
    for (std::map<t_keytype, boost::shared_ptr<BSONContent> >::const_iterator it = _elements.begin(); it != _elements.end(); it++) {
        t_keytype itKey = it->first;
        if (itKey.compare(key) == 0) {
            return true;
        }
    }
    return false;
}
