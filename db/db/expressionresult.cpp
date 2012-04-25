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

ExpressionResult::ExpressionResult(RESULT_TYPE type, void* value) {
	_type = type;
	_value = value;
}

ExpressionResult::ExpressionResult(const ExpressionResult& orig) {
	this->_type = orig._type;
	this->_value = orig._value;
}

ExpressionResult::~ExpressionResult() {
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


RESULT_TYPE ExpressionResult::type() {
	return _type;
}

void* ExpressionResult::value() {
	return _value;
}




