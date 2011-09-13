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
    BSONCONTENT_FILL(key, INT, &val);
}

void BSONObj::add(char* key, double val) {
    BSONCONTENT_FILL(key, DOUBLE, &val);
}

void BSONObj::add(char* key, long val) {
    BSONCONTENT_FILL(key, LONG, &val);
}

void BSONObj::add(char* key, char* val) {
    BSONCONTENT_FILL(key, PTRCHAR, val);
}

void BSONObj::add(char* key, std::string val) {
    BSONCONTENT_FILL(key, STRING, &val);
}

void BSONObj::add(char* key, BSONObj* val) {
    BSONCONTENT_FILL(key, BSON, val);
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
            case BSON:
                ss << ((BSONObj*)content->_element)->toChar();
                break;
            case INT:
                ss << "'" << *((int*)content->_element) << "'";
                break;
            case LONG:
                ss << "'" << *((long*)content->_element) << "'";
                break;
            case DOUBLE:
                ss << "'" << *((double*)content->_element) << "'";
                break;
            case PTRCHAR:
                ss << "'" << (char*)content->_element << "'";
                break;
            case STRING:
                ss << "'" << ((std::string*)content->_element)->c_str() << "'";
                break;
        }
    }
    ss << "} ";
    std::string s = ss.str();
    const char* temp = s.c_str();
    int len = s.length();
    char* res = (char*)malloc(len);
    memcpy(res, temp, len);
    return res;
}
