/*
 * =====================================================================================
 *
 *       Filename:  expressionresult.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/24/2012 10:14:02 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "filterparser.h"
#include "bson.h"
#include <assert.h>

void* copyValue(RESULT_TYPE type, void* value) {
	void* result = NULL;
	switch (type) {
		case RT_INT:
			{
				int* i = new int();
				*i = *(int*)value;
				result = i;
				break;
			}
		case RT_DOUBLE:
			{
				double* d = new double();
				*d = *(double*)value;
				result = d;
				break;
			}
		case RT_BOOLEAN:
			{
				bool* b = new bool();
				*b = *(bool*)value;
				result = b;
				break;
			}
		case RT_BSON:
			{
				BSONObj* o = new BSONObj(*(BSONObj*)value);
				result = o;
				break;
			}

		case RT_STRING:
			{
				std::string* s = new std::string(*(std::string*)value);
				result = s;
				break;
			}
		case RT_NULL:
			break;
		default:
			assert(false);
			break;
	}

	return result;
}

ExpressionResult::ExpressionResult(RESULT_TYPE type, void* value) {
	_type = type;
	_value = copyValue(_type, value);
}

ExpressionResult::ExpressionResult(const ExpressionResult& orig) {
	this->_type = orig._type;
	this->_value = copyValue(this->_type, orig._value);
}

ExpressionResult::~ExpressionResult() {
	if (_value) {
		switch (_type) {
			case RT_INT:
				delete ((int*)_value);
				break;
			case RT_DOUBLE:
				delete ((double*)_value);
				break;
			case RT_BOOLEAN:
				delete ((bool*)_value);
				break;
			case RT_BSON:
				delete ((BSONObj*)_value);
				break;
		}
	}
	_value = NULL;
}


RESULT_TYPE ExpressionResult::type() {
	return _type;
}

void* ExpressionResult::value() {
	return _value;
}




