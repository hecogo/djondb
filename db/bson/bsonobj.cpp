#include "bsonobj.h"
#include "util.h"

#include "bsonparser.h"

#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

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

void BSONObj::add(t_keytype key, const BSONObj& val) {
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
		ss << "\"" << key << "\" :";
		switch (content->type())  {
			case BSON_TYPE:
				ss << ((BSONObj*)content->_element)->toChar();
				break;
			case INT_TYPE:
				ss << *((int*)content->_element);
				break;
			case LONG_TYPE:
				ss << *((long*)content->_element);
				break;
			case DOUBLE_TYPE:
				ss << *((double*)content->_element);
				break;
			case PTRCHAR_TYPE:
				ss << "\"" << (char*)content->_element << "\"";
				break;
			case STRING_TYPE:
				ss << "\"" << ((std::string*)content->_element)->c_str() << "\"";
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
	BSONContent* content = getContent(key, INT_TYPE);
	if (content != NULL) {
		int* res = (int*)content->_element;
		return res;
	} else {
		return NULL;
	}
}

double* BSONObj::getDouble(t_keytype key) const {
	BSONContent* content = getContent(key, DOUBLE_TYPE);
	if (content != NULL) {
		double* res = (double*)content->_element;
		return res;
	} else {
		return NULL;
	}
}

long* BSONObj::getLong(t_keytype key) const {
	BSONContent* content = getContent(key, LONG_TYPE);
	if (content != NULL) {
		long* res = (long*)content->_element;
		return res;
	} else {
		return NULL;
	}
}

char* BSONObj::getChars(t_keytype key) const {
	BSONContent* content = getContent(key, PTRCHAR_TYPE);
	if (content != NULL) {
		char* res = (char*)content->_element;
		return res;
	} else {
		return NULL;
	}
}

std::string* BSONObj::getString(t_keytype key) const {
	BSONContent* content = NULL;
	std::string* result = NULL;
	for (std::map<t_keytype, BSONContent* >::const_iterator it = _elements.begin(); it != _elements.end(); it++) {
		t_keytype itKey = it->first;
		if (itKey.compare(key) == 0) {
			content = it->second;
			if (content->type() != STRING_TYPE) {
				if (content->type() == PTRCHAR_TYPE) {
					result = new std::string((char*)content->_element);
				} else {
					throw "The type does not match the requested STRING";
				}
			} else {
				result = (std::string*)content->_element;
			}
			break;
		}
	}
	return result;
}

BSONObj* BSONObj::getBSON(t_keytype key) const {
	BSONContent* content = getContent(key, BSON_TYPE);
	if (content != NULL) {
		BSONObj* res = (BSONObj*)content->_element;
		return res;
	} else {
		return NULL;
	}
}

BSONContent* BSONObj::getContent(t_keytype key) const {
	BSONContent* content = NULL;
	for (std::map<t_keytype, BSONContent* >::const_iterator it = _elements.begin(); it != _elements.end(); it++) {
		t_keytype itKey = it->first;
		if (itKey.compare(key) == 0) {
			content = it->second;
			break;
		}
	}
	return content;
}

BSONContent* BSONObj::getContent(t_keytype key, BSONTYPE ttype) const {
	BSONContent* content = getContent(key);
	if (content != NULL) {
		if (content->type() != ttype) {
			cout << "The type " << content->type() << " does not match the requested STRING for key2: " << key << endl; \
				throw "type does not match";
		}
	}
	return content;
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

bool BSONObj::has(t_keytype key) const {
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

BSONTYPE BSONObj::type(t_keytype key) const {
	BSONContent* content = NULL;
	//    SEARCHBSON(key, STRING_TYPE);
	for (std::map<t_keytype, BSONContent* >::const_iterator it = _elements.begin(); it != _elements.end(); it++) {
		t_keytype itKey = it->first;
		if (itKey.compare(key) == 0) {
			content = it->second;
			break;
		}
	}
	if (content != NULL) {
		return content->type();
	} else {
		return UNKNOWN_TYPE;
	}
}

void* BSONObj::get(t_keytype key) const {
	BSONContent* content = NULL;
	//    SEARCHBSON(key, STRING_TYPE);
	for (std::map<t_keytype, BSONContent* >::const_iterator it = _elements.begin(); it != _elements.end(); it++) {
		t_keytype itKey = it->first;
		if (itKey.compare(key) == 0) {
			content = it->second;
			break;
		}
	}
	if (content != NULL) {
		return content->_element;
	} else {
		return NULL;
	}
}
