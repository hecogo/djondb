// *********************************************************************************************************************
// file:
// author: Juan Pablo Crossley (crossleyjuan@gmail.com)
// created:
// updated:
// license:
// 
// This file is part of the djondb project, for license information please refer to the LICENSE file,
// the application and libraries are provided as-is and free of use under the terms explained in the file LICENSE
// Its authors create this application in order to make the world a better place to live, but you should use it on
// your own risks.
// 
// Also, be adviced that, the GPL license force the committers to ensure this application will be free of use, thus
// if you do any modification you will be required to provide it for free unless you use it for personal use (you may 
// charge yourself if you want), bare in mind that you will be required to provide a copy of the license terms that ensures
// this program will be open sourced and all its derivated work will be too.
// *********************************************************************************************************************

#include "bsonobj.h"
#include "util.h"

#include "bsonparser.h"

#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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

void BSONObj::add(t_keytype key, const BSONArrayObj& val) {
	BSONArrayObj* internalValue = new BSONArrayObj(val);
	BSONCONTENT_FILL(key, BSONARRAY_TYPE, internalValue);
}


char* BSONObj::toChar() const {
	char result[2000];
	memset(result, 0, 2000);

	int pos = 0;
	result[0] = '{';
	pos += 1;

	bool first = true;
	
	for (std::map<t_keytype, BSONContent* >::const_iterator i = _elements.begin(); i != _elements.end(); i++) {
		if (!first) {
			result[pos] = ',';
			pos++;
		}
		first = false;
		BSONContent* content = i->second;
		t_keytype key = i->first;
		sprintf(result + pos, " \"%s\" : ", key.c_str());
		pos += key.length() + 6;
		//ss << "\"" << key << "\" :";
		switch (content->type())  {
			case BSON_TYPE:
				{
					char* bchar = ((BSONObj*)content->_element)->toChar();
					sprintf(result + pos, "%s", bchar);
					pos += strlen(bchar);
					break;
				}
			case BSONARRAY_TYPE:
				{
					char* achar = ((BSONArrayObj*)content->_element)->toChar();
					sprintf(result + pos, "%s", achar);
					pos += strlen(achar);
					break;
				}
			case INT_TYPE: 
				{
					sprintf(result + pos, "%d", *((int*)content->_element));
					pos = strlen(result);
					break;
				}
			case LONG_TYPE:
				{
					sprintf(result + pos, "%ld", *((long*)content->_element));
					pos = strlen(result);
					break;
				}
			case DOUBLE_TYPE:
				{
					sprintf(result + pos, "%f", *((double*)content->_element));
					pos = strlen(result);
					break;
				}
			case PTRCHAR_TYPE:
				{
					char* c = (char*)content->_element;
					sprintf(result + pos, "\"%s\"", c);
					pos += strlen(c) + 2;
					break;
				}
			case STRING_TYPE:
				{
					const char* c = ((std::string*)content->_element)->c_str();
					sprintf(result + pos, "\"%s\"", c);
					pos += strlen(c) + 2;
					break;
				}
		}
	}
	result[pos] = '}';
	return strdup(result);
}

int* BSONObj::getInt(t_keytype key) const {
	BSONContent* content = getContent(key);
	if ((content != NULL) && (content->type() == INT_TYPE)) {
		int* res = (int*)content->_element;
		return res;
	} else {
		return NULL;
	}
}

double* BSONObj::getDouble(t_keytype key) const {
	BSONContent* content = getContent(key);
	if ((content != NULL) && (content->type() == DOUBLE_TYPE)) {
		double* res = (double*)content->_element;
		return res;
	} else {
		return NULL;
	}
}

long* BSONObj::getLong(t_keytype key) const {
	BSONContent* content = getContent(key);
	if ((content != NULL) && (content->type() == LONG_TYPE)) {
		long* res = (long*)content->_element;
		return res;
	} else {
		return NULL;
	}
}

char* BSONObj::getChars(t_keytype key) const {
	BSONContent* content = getContent(key);
	if (content != NULL) {
		if (content->type() == PTRCHAR_TYPE) {
			return (char*)content->_element;
		} if (content->type() == STRING_TYPE) {
			return const_cast<char*>(((std::string*)content->_element)->c_str());
		} else {
			return NULL;
		}
	} else {
		return NULL;
	}
}

std::string BSONObj::getString(t_keytype key) const {
	BSONContent* content = getContent(key);
	if (!content) {
		return std::string();
	}
	std::string result;
	if (content->type() == PTRCHAR_TYPE) {
		result = std::string((char*)content->_element);
	} else if (content->type() == STRING_TYPE) {
		result = *(std::string*)content->_element;
	} else {
		assert(false);
	}
	return result;
}

BSONObj* BSONObj::getBSON(t_keytype key) const {
	BSONContent* content = getContent(key);
	if ((content != NULL) && (content->type() == BSON_TYPE)) {
		BSONObj* res = (BSONObj*)content->_element;
		return res;
	} else {
		return NULL;
	}
}

BSONArrayObj* BSONObj::getBSONArray(t_keytype key) const {
	BSONContent* content = getContent(key);
	if ((content != NULL) && (content->type() == BSONARRAY_TYPE)) {
		BSONArrayObj* res = (BSONArrayObj*)content->_element;
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

BSONContent BSONObj::getXpath(const std::string& xpath) const {
	int posDot = xpath.find('.');
	if (posDot == string::npos) {
		BSONContent* result = getContent(xpath);
		if (result != NULL) {
			return *result;
		} else {
			return BSONContent(); // this will return a NULL_TYPE
		}
	} else {
		std::string path = xpath.substr(0, posDot);
		BSONContent* content = getContent(path);
		if (content == NULL) {
			return BSONContent();
		}
		if (content->type() == BSON_TYPE) {
			BSONObj inner = (BSONObj)*content;
			return inner.getXpath(xpath.substr(posDot + 1));
		} else {
			return BSONContent();
		}
	}

	return BSONContent();
}
