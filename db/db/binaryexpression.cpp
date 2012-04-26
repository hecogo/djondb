// =====================================================================================
//  Filename:  binaryexpression.cpp
// 
//  Description:  
// 
//  Version:  1.0
//  Created:  04/24/2012 10:42:29 AM
//  Revision:  none
//  Compiler:  gcc
// 
//  Author:  YOUR NAME (), 
// 
// License:
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
// =====================================================================================

#include "filterparser.h"

BinaryExpression::BinaryExpression(FILTER_OPERATORS oper)
   :BaseExpression(ET_BINARY)
{
	_oper = oper;
	_left = NULL;
	_right = NULL;
}

BinaryExpression::BinaryExpression(const BinaryExpression& orig)
	:BaseExpression(ET_SIMPLE)
{
	_oper = orig._oper;
	_left = orig._left;
	_right = orig._right;
}

ExpressionResult* evalEqual(const BSONObj& bson, BaseExpression* left, BaseExpression* right) {
	ExpressionResult* valLeft = left->eval(bson);
	ExpressionResult* valRight = right->eval(bson);
	
	bool result = false;
	if (valLeft->type() != valRight->type()) {
		result = false;
	}

	if (((valLeft->value() != NULL) && (valRight->value() == NULL)) ||
			((valLeft->value() == NULL) && (valRight->value() != NULL))) {
		result = false;
	}

	if (valLeft->value() == valRight->value()) {
		result = true;
	}

	// the types are ensured to be equal
	switch (valLeft->type()) {
		case RT_INT:
			result = (*(int*)valLeft->value() == *(int*)valRight->value());
			break;
		case RT_DOUBLE:
			result = (*(double*)valLeft->value() == *(double*)valRight->value());
			break;
		case RT_BOOLEAN:
			result = (*(bool*)valLeft->value() == *(bool*)valRight->value());
			break;
		case RT_STRING:
			{
				std::string* leftS = (std::string*)valLeft->value();
				std::string* rightS = (std::string*)valRight->value();
				result = (leftS->compare(*rightS) == 0);
			}
			break;
		case RT_BSON:
			result = false;
			break;
	}
	bool* b = new bool();
	*b = result;
	return new ExpressionResult(RT_BOOLEAN, b);
}

ExpressionResult* evalAndOr(const BSONObj& bson, FILTER_OPERATORS oper, BaseExpression* left, BaseExpression* right) {
	ExpressionResult* valLeft = left->eval(bson);
	ExpressionResult* valRight = right->eval(bson);

	if ((valLeft->type() != RT_BOOLEAN) || (valRight->type() != RT_BOOLEAN)) {
		// ERROR
		return NULL;
	} else {
		bool* bleft = (bool*)valLeft->value();
		bool* bright = (bool*)valRight->value();

		bool* bresult = new bool();
		switch (oper) {
			case FO_AND:
				*bresult = (*bleft && *bright);
				break;
			case FO_OR:
				*bresult = (*bleft ||  *bright);
				break;
		}
		ExpressionResult* result = new ExpressionResult(RT_BOOLEAN, bresult);
		return result;
	}
}

ExpressionResult* BinaryExpression::eval(const BSONObj& bson) {

	switch (_oper) {
		case FO_EQUALS:
			return evalEqual(bson, _left, _right);
		case FO_AND:
			return evalAndOr(bson, _oper, _left, _right);
	}
}

BaseExpression* BinaryExpression::copyExpression() {
	BinaryExpression* result = new BinaryExpression(this->oper());
	if (_left != NULL) {
		result->_left = _left->copyExpression();
	}
	if (_right != NULL) {
		result->_right = _right->copyExpression();
	}
	return result;
}

void BinaryExpression::push(BaseExpression* expression) {

	if (_left == NULL) {
		_left = expression;
	} else if (_right == NULL) {
		_right = expression;
	} else {
		// ERROR
	}
}


FILTER_OPERATORS BinaryExpression::oper() const {
	return _oper;
}
