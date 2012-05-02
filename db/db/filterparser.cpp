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

BaseExpression* solveToken(Token* token) {
	BaseExpression* result = NULL;
	EXPRESSION_TYPE extype;
	FILTER_OPERATORS oper;
	switch (token->type()) {
		case TT_EQUALS:
			extype = ET_BINARY;
			oper = FO_EQUALS;
			break;
		case TT_AND:
			extype = ET_BINARY;
			oper = FO_AND;
			break;
		case TT_CONSTANT:
			extype = ET_CONSTANT;
			break;
		case TT_EXPRESION:
			extype = ET_SIMPLE;
			break;
	}
	switch (extype) {
		case ET_SIMPLE: 
			result = new SimpleExpression(*token->content());
			break;
		case ET_BINARY:
			result = new BinaryExpression(oper);

			break;	
	}
	return result;	
}

BaseExpression* solveExpression(std::list<Token*> tokens, std::list<Token*>::iterator& i) {
	Token* token = *i;
	std::list<BaseExpression*> waitingList;
	while ((token->type() != TT_CLOSEPARENTESIS) && (i != tokens.end())) {
		BaseExpression* tempExpression = NULL;

		BaseExpression* expression = solveToken(token);
		switch(expression->type()) {
			case ET_SIMPLE:
				break;	  
			case ET_BINARY:
				((BinaryExpression*)expression)->push(waitingList.back());
				waitingList.pop_back();
				i++;
				((BinaryExpression*)expression)->push(solveExpression(tokens, i));
				break;
		}
		waitingList.push_back(expression);

		i++;
		token = *i;
	}

	if (waitingList.size() == 1) {
		return waitingList.back();
	} else {
		// ERROR 
		return NULL;
	}
}

BaseExpression* solveParentesis(std::list<Token*> tokens, std::list<Token*>::iterator& i) {
	Token* currentToken = *i;
	if (currentToken->type() == TT_OPENPARENTESIS) {
		i++;
		solveParentesis(tokens, i);
	}
	BaseExpression* expression = solveExpression(tokens, i);
	// Jumps the last parentesis
	i++;
	return expression;
}

BaseExpression* createTree(std::list<Token*> tokens) {
	// process binary operators

	// Reduce binaries
	for (std::list<Token*>::iterator i = tokens.begin(); i != tokens.end(); i++) {
		Token* token = *i;
		if (token->type() == TT_OPENPARENTESIS) {
			i++;
			BaseExpression* express = solveParentesis(tokens, i);
		}
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


