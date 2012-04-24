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
}

BinaryExpression::BinaryExpression(const BinaryExpression& orig)
	:BaseExpression(ET_SIMPLE)
{
}


void* BinaryExpression::eval(const BSONObj& bson) {
	void* valLeft = _left->eval(bson);
	void* valRight = _right->eval(bson);

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
