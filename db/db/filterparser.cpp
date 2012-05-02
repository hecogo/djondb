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

TOKEN_TYPE checkTokenType(char* buffer) {
	TOKEN_TYPE type = TT_CONSTANT;
	if (strcmp(buffer, "==") == 0) {
		type = TT_EQUALS;
	} else if (strcasecmp(buffer, "and") == 0) {
		type = TT_AND;
	}
	return type;
}

BaseExpression* createTree(std::list<Token*> tokens) {
	// process binary operators
	
	BaseExpression* root = NULL;
	std::list<Token*> waitList;
	while (tokens.size() > 1) {
		while (tokens.size() > 0) {

			Token* token = tokens.front();
			tokens.pop_front();

			switch (exp->type()) {
				case ET_UNARY:
					if (!waitList.empty()) {
						BaseExpression* b1 = waitList.back();
						waitList.pop_back();
						((UnaryExpression*)exp)->push(b1);
					} else {
						// ERROR
					}
					waitList.push_front(exp);
					break;
				case ET_BINARY:
					if (waitList.size() == 0) {
						// ERROR
					}
					((BinaryExpression*)exp)->push(waitList.back());
					waitList.pop_back();
					if (!tokens.empty()) {
						BaseExpression* b1 = tokens.front();
						tokens.pop_front();
						((BinaryExpression*)exp)->push(b1);
					} else {
						// ERROR
					}
					waitList.push_back(exp);

					break;
				default:
					waitList.push_back(exp);
					break;
			}
		}
		for (std::list<BaseExpression*>::iterator i = waitList.begin(); i != waitList.end(); i++) {
			tokens.push_back(*i);
		}
		waitList.clear();
	}

	return NULL;// tokens.front();
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

	TOKEN_TYPE token_type;//= TT_NOTSELECTED;

	std::list<Token*> tokens;
	BaseExpression* rootExpression = NULL;
	bool strOpen = false;
	char startStringChar = '\'';
	const char* VALID_CHARS = "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_";
	const char* OPERATORS[] = { "==", "and", "<", "<=", ">", ">=", "!" };
	int openParentesis = 0;
	FILTER_OPERATORS lastOperator;

	while (pos < len) {
		bool charProcessed = false;
		if ((chrs[pos] == '\'') || (chrs[pos] == '\"')) {
			startStringChar = chrs[pos];
			bool escaped = false;
			do {
				buffer[posBuffer] = chrs[pos];
				posBuffer++;
				pos++;
			} while (chrs[pos] != startStringChar);
			buffer[posBuffer] = chrs[pos];
			posBuffer++;
			pos++;
			tokens.push_back(new Token(checkTokenType(buffer), std::string(buffer)));
			memset(buffer, 0, BUFFER_SIZE);
			posBuffer = 0;
		} else if ((!strOpen) && (chrs[pos] == '(')) {
			tokens.push_back(new Token(TT_OPENPARENTESIS));
			openParentesis++;
			charProcessed = true;
		} else if ((!strOpen) && (chrs[pos] == ')')) {
			tokens.push_back(new Token(TT_CLOSEPARENTESIS));
			charProcessed = true;
			openParentesis--;
			if (openParentesis < 0) {
				// ERROR
			}
		} else if (strchr(VALID_CHARS, chrs[pos]) == NULL) {
			if (strlen(buffer) > 0) {
				TOKEN_TYPE type = checkTokenType(buffer);
				tokens.push_back(new Token(type, std::string(buffer)));

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
		tokens.push_back(new Token(TT_CONSTANT, buffer));
	}

	rootExpression = createTree(tokens);


	FilterParser* parser = new FilterParser(expression, rootExpression);

	return parser;
}


