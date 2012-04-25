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

	std::queue<BaseExpression*> expressionsqueue;
	BaseExpression* rootExpression = NULL;
	bool strOpen = false;
	char startStringChar = '\'';
	const char* SEPARATORS = " ";

	while (pos < len) {
		bool charProcessed = false;
		if ((chrs[pos] == '$') && (!strOpen)) {
			token_type = TT_SIMPLEEXPRESSION;
			charProcessed = true;
		} else {
			bool tokenFound = false;
			if (!strOpen && ((chrs[pos] == '\'') || (chrs[pos] == '\"'))) {
				startStringChar = chrs[pos];
				strOpen = true;
				charProcessed = true;
			} else if (strOpen && (chrs[pos] == startStringChar)) {
				strOpen = false;
				tokenFound = true;
				charProcessed = true;
			}
			if (!tokenFound && (strchr(SEPARATORS, chrs[pos]) != NULL)) {
				tokenFound = true;
				charProcessed = true;
			}
			// the Buffer contains a 'ready' token
			if (tokenFound) {
				if (strlen(buffer) > 0) {
					BaseExpression* current = createExpression(token_type, buffer);
					memset(buffer, 0, BUFFER_SIZE);
					posBuffer = 0;
					expressionsqueue.push(current);
					token_type = TT_NOTSELECTED;
				}
			} else {
				if (!charProcessed) {
					buffer[posBuffer] = chrs[pos];
					posBuffer++;
				}
			}
		}

		pos++;
	}

	if (strlen(buffer) > 0) {
		expressionsqueue.push(createExpression(token_type, buffer));
	}

	rootExpression = createTree(expressionsqueue);


	FilterParser* parser = new FilterParser(expression, rootExpression);

	return parser;
}

BaseExpression* FilterParser::createTree(std::queue<BaseExpression*> expressions) {
	BaseExpression* root = NULL;
	BaseExpression* current = NULL;
	while (!expressions.empty()) {

		BaseExpression* exp = expressions.front();
		expressions.pop();
		if (root == NULL) {
			root = exp;
			current = exp;
		} else {
			// ERROR!
		}

		UnaryExpression* unary;
		BinaryExpression* binary;
		switch (exp->type()) {
			case ET_UNARY:
				unary = (UnaryExpression*)exp;
				if (!expressions.empty()) {
					BaseExpression* b1 = expressions.front();
					expressions.pop();
					unary->push(b1);
					current = unary;
				} else {
					// ERROR
				}
				break;
			case ET_BINARY:
				binary = (BinaryExpression*)exp;
				binary->push(current);
				current = binary;
				if (!expressions.empty()) {
					BaseExpression* b1 = expressions.front();
					expressions.pop();
					binary->push(b1);
				} else {
					// ERROR
				}

				break;
		}
	}

	return root;
}

BaseExpression* FilterParser::createExpression(TOKEN_TYPE token_type, const char* buffer) {
	if (token_type == TT_NOTSELECTED) {
		token_type = TT_CONSTANTEXPRESSION;
	}
	BaseExpression* result = NULL;
	switch (token_type) {
		case TT_NOTSELECTED:
			if (strcmp(buffer, "==") == 0) {
				result = new BinaryExpression(FO_EQUALS);
			}
			break;
		case TT_SIMPLEEXPRESSION:
			result = new SimpleExpression(std::string(buffer));
			break;
		case TT_CONSTANTEXPRESSION:
			result = new ConstantExpression(std::string(buffer));
			break;
	}

	return result;
}

BinaryExpression* FilterParser::parseAND(char* chars, int index, int len) {
}



