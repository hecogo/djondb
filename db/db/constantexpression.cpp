// =====================================================================================
//  Filename:  simpleexpression.cpp
// 
//  Description: Implementation of the "Constant" expressions, like ints, strings, double, etc
// 
//  Version:  1.0
//  Created:  04/24/2012 10:42:09 AM
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

#include "constantexpression.h"
#include "bson.h"
#include <assert.h>

ConstantExpression::ConstantExpression(const char* expression)
	:BaseExpression(ET_CONSTANT)
{
	_expression = expression;
	_value = NULL;
	parseConstantExpression();
}

ConstantExpression::ConstantExpression(const ConstantExpression& orig)
	:BaseExpression(ET_CONSTANT)
{
	_expression = orig._expression;
	if (orig._value) {
		_value = new ExpressionResult(*orig._value);
	} else {
		_value = NULL;
	}
}

ConstantExpression::~ConstantExpression() {
	if (_value) {
		delete _value;
	}
	_value = NULL;
}

ExpressionResult* ConstantExpression::eval(const BSONObj& bson) {
	ExpressionResult* result = new ExpressionResult(*_value);
	return result; 
}

BaseExpression* ConstantExpression::copyExpression() {
	ConstantExpression* result = new ConstantExpression(this->_expression);
	return result;
}

void ConstantExpression::parseConstantExpression() {
	if (strchr("0123456789.", _expression[0]) != NULL) {
		if (strchr(_expression, '.') != NULL) {
			double d = atof(_expression);
			_value = new ExpressionResult(ExpressionResult::RT_DOUBLE, &d);
		} else {
			int i = atoi(_expression);
			_value = new ExpressionResult(ExpressionResult::RT_INT, &i);
		}
	} else if ((_expression[0] == '\'') || (_expression[0] == '\"')) {
		std::string s(std::string(_expression).substr(1, strlen(_expression) - 2));
		_value = new ExpressionResult(ExpressionResult::RT_STRINGDB, &s);
	} else {
		assert(false);
	}
}

