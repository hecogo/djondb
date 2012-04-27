// =====================================================================================
//  Filename:  unaryexpression.cpp
// 
//  Description:  
// 
//  Version:  1.0
//  Created:  04/24/2012 10:42:18 AM
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

UnaryExpression::UnaryExpression(FILTER_OPERATORS oper)
	:BaseExpression(ET_UNARY)
{
	_expression = NULL;
	_oper = oper;
}

UnaryExpression::UnaryExpression(const UnaryExpression& orig)
	:BaseExpression(ET_UNARY)
{
	if (orig._expression != NULL) {
		this->_expression = _expression->copyExpression();
	}
}

ExpressionResult* UnaryExpression::eval(const BSONObj& bson) {
	switch (_oper) {
		case FO_PARENTESIS:
			return _expression->eval(bson);
	}
	return NULL;
}

BaseExpression* UnaryExpression::copyExpression() {
	UnaryExpression* result = new UnaryExpression(_oper);
	if (_expression != NULL) {
		result->push(_expression);
	}
	return result;
}

void UnaryExpression::push(BaseExpression* expression) {

	if (_expression == NULL) {
		_expression = expression;
	} else {
		// ERROR
	}
}

