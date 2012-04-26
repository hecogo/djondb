// =====================================================================================
//  Filename:  filterparser.cpp
// 
//  Description:  This file contains the implementation of the expression parser used
//                to create the vocabulary and the logic to analyze where expressions.
// 
//  Version:  1.0
//  Created:  04/24/2012 09:45:47 AM
//  Revision:  none
//  Compiler:  gcc
// 
//  Author:  Juan Pablo Crossley (crossley@gmail.com), 
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
#include <string.h>
#include <strings.h>

FilterParser::FilterParser(const std::string& expression, BaseExpression* root):
	_expression(expression)
{
	_root = root;
}

FilterParser::FilterParser(const FilterParser& orig) {
	_expression = orig._expression;
	if (orig._root != NULL) {
		EXPRESSION_TYPE type = orig._root->type();
		switch (type) {
			case ET_SIMPLE:
				_root = new SimpleExpression(*(SimpleExpression*)orig._root);
				break;
			case ET_UNARY:
				_root = new UnaryExpression(*(UnaryExpression*)orig._root);
				break;
			case ET_BINARY:
				_root = new BinaryExpression(*(BinaryExpression*)orig._root);
				break;
		}
	}
}

FilterParser::~FilterParser() {
	delete _root;
}

ExpressionResult* FilterParser::eval(const BSONObj& bson) {
	ExpressionResult* result = NULL;
	if (_root != NULL) {
		result = _root->eval(bson);
	}

	return result;
}

FILTER_OPERATORS checkOperator(char* buffer) {
	FILTER_OPERATORS oper = FO_NOTOPERATOR;
	if (strcmp(buffer, "==") == 0) {
		oper = FO_EQUALS;
	} else if (strcasecmp(buffer, "and") == 0) {
		oper = FO_AND;
	}
	return oper;
}

// static
FilterParser* FilterParser::parse(const std::string& expression) {
	const char* chrs = expression.c_str();

	const int BUFFER_SIZE = 1024;
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);
	int pos = 0;
	int posBuffer = 0;
	int len = strlen(chrs);

	TOKEN_TYPE token_type = TT_NOTSELECTED;

	std::list<BaseExpression*> expressions;
	BaseExpression* rootExpression = NULL;
	bool strOpen = false;
	char startStringChar = '\'';
	const char* SEPARATORS = " ";
	int openParentesis = 0;
	FILTER_OPERATORS lastOperator;

	while (pos < len) {
		bool charProcessed = false;
		if ((chrs[pos] == '$') && (!strOpen)) {
			token_type = TT_SIMPLEEXPRESSION;
			charProcessed = true;
		} else if (!strOpen && ((chrs[pos] == '\'') || (chrs[pos] == '\"'))) {
			startStringChar = chrs[pos];
			strOpen = true;
			charProcessed = true;
		} else if (strOpen && (chrs[pos] == startStringChar)) {
			strOpen = false;
			charProcessed = true;
			if (token_type == TT_SIMPLEEXPRESSION) {
				expressions.push_back(new SimpleExpression(std::string(buffer)));
				token_type = TT_NOTSELECTED;
				memset(buffer, 0, BUFFER_SIZE);
				posBuffer = 0;
			}
		} else if ((!strOpen) && (chrs[pos] == '(')) {
			openParentesis++;
			charProcessed = true;
		} else if ((!strOpen) && (chrs[pos] == ')')) {
			expressions.push_back(new UnaryExpression(FO_PARENTESIS));
			charProcessed = true;
			openParentesis--;
			if (openParentesis < 0) {
				// ERROR
			}
		} else if (strchr(SEPARATORS, chrs[pos]) != NULL) {
			charProcessed = true;
			if (strlen(buffer) > 0) {
				FILTER_OPERATORS oper = checkOperator(buffer);
				BaseExpression* expr = NULL;
				switch (oper) {
					case FO_NOTOPERATOR:
						expr = new ConstantExpression(buffer);
						break;
					case FO_EQUALS:
					case FO_AND:
						expr = new BinaryExpression(oper);
						break;
					default:
						//ERROR
						break;
				}

				expressions.push_back(expr);
				memset(buffer, 0, BUFFER_SIZE);
				posBuffer = 0;
			}
		} else if (!charProcessed) {
			buffer[posBuffer] = chrs[pos];
			posBuffer++;
		}

		pos++;
	}

	if (strlen(buffer) > 0) {
		// all the other options has been processed, if the buffer contains something
		// it should be a constant
		expressions.push_back(new ConstantExpression(buffer));
	}

	rootExpression = createTree(expressions);


	FilterParser* parser = new FilterParser(expression, rootExpression);

	return parser;
}

BaseExpression* FilterParser::createTree(std::list<BaseExpression*> expressions) {
	BaseExpression* root = NULL;
	BaseExpression* last = NULL;
	while (expressions.size() > 1) {

		BaseExpression* exp = expressions.front();
		expressions.pop_front();

		switch (exp->type()) {
			case ET_UNARY:
				if (!expressions.empty()) {
					BaseExpression* b1 = expressions.front();
					expressions.pop_front();
					((UnaryExpression*)exp)->push(b1);
				} else {
					// ERROR
				}
				expressions.push_front(exp);
				last = NULL;
				break;
			case ET_BINARY:
				if (last == NULL) {
					// ERROR
				}
				((BinaryExpression*)exp)->push(last);
				if (!expressions.empty()) {
					BaseExpression* b1 = expressions.front();
					expressions.pop_front();
					((BinaryExpression*)exp)->push(b1);
				} else {
					// ERROR
				}
				expressions.push_front(exp);

				break;
		}
		if (last != NULL) {
			// ERROR an expression was not processed
		}
		last = exp;
	}

	return expressions.front();
}


