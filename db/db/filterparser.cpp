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

BaseExpression* solveExpression(std::list<Token*>& tokens, std::list<Token*>::iterator& i);
const int BUFFER_SIZE = 1024;

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
	} else {
		bool* bres = new bool();
		*bres = true;
		result = new ExpressionResult(RT_BOOLEAN, bres);
	}

	return result;
}

TOKEN_TYPE checkTokenType(const char* chrs, int& pos) {
	std::list<char*> matchOperators;
	matchOperators.push_back("(");
	matchOperators.push_back(")");
	matchOperators.push_back("==");
	matchOperators.push_back("and");
	matchOperators.push_back("or");
	matchOperators.push_back("<");
	matchOperators.push_back(">");
	matchOperators.push_back("!");

	char buffer[1024];
	memset(buffer, 0, 1024);
	int posBuffer = 0;

	TOKEN_TYPE type = TT_NOTTOKEN;

	while (true) {
		buffer[posBuffer] = chrs[pos];
		posBuffer++;
		std::list<char*> newmatch;
		for (std::list<char*>::iterator i = matchOperators.begin(); i != matchOperators.end(); i++) {
			char* oper = *i;
			if (strncmp(oper, buffer, posBuffer) == 0) {
				newmatch.push_back(oper);
			}
			if (strcmp(oper, buffer) == 0) {
				if (strcmp(buffer, "==") == 0) {
					type = TT_EQUALS;
				} else if (strcmp(buffer, "and") == 0) {
					type = TT_AND;
				} else if (strcmp(buffer, "or") == 0) {
					type = TT_OR;
				} else if (strcmp(buffer, "(") == 0) {
					type = TT_OPENPARENTESIS;
				} else if (strcmp(buffer, ")") == 0) {
					type = TT_CLOSEPARENTESIS;
				} else if (strcmp(buffer, "<") == 0) {
					if (chrs[pos] == '=') {
						type = TT_LESSEQUALTHAN;
					} else {
						type = TT_LESSTHAN;
					}
				} else if (strcmp(buffer, ">") == 0) {
					if (chrs[pos] == '=') {
						type = TT_GREATEREQUALTHAN;
					} else {
						type = TT_GREATERTHAN;
					}
				}
				return type;
				// FOUND
			}
		}
		pos++;
		matchOperators.clear();
		matchOperators.insert(matchOperators.begin(), newmatch.begin(), newmatch.end());
		if (matchOperators.size() == 0) {
			break;
		}
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
		case TT_OR:
			extype = ET_BINARY;
			oper = FO_OR;
			break;
		case TT_CONSTANT:
			extype = ET_CONSTANT;
			break;
		case TT_EXPRESION:
			extype = ET_SIMPLE;
			break;
	}
	switch (extype) {
		case ET_CONSTANT:
			result = new ConstantExpression(*token->content());
			break;
		case ET_SIMPLE: 
			result = new SimpleExpression(*token->content());
			break;
		case ET_BINARY:
			result = new BinaryExpression(oper);

			break;	
	}
	return result;	
}

BaseExpression* solveParentesis(std::list<Token*>& tokens, std::list<Token*>::iterator& i) {
	BaseExpression* expression;
	// Jumps the starting parentesis
	i++;
	//Token* currentToken = *i;
//	if (currentToken->type() == TT_OPENPARENTESIS) {
//		expression = solveParentesis(tokens, i);
//	} else {
		expression = solveExpression(tokens, i);
		i++;
//	}
	return expression;
}

BaseExpression* solveExpression(std::list<Token*>& tokens, std::list<Token*>::iterator& i) {
	std::list<BaseExpression*> waitingList;
	while (i != tokens.end()) {
		Token* token = *i;
		if (token->type() == TT_CLOSEPARENTESIS) {
			break;
		}
		BaseExpression* tempExpression = NULL;

		BaseExpression* expression = NULL;
		if (token->type() == TT_OPENPARENTESIS) {
			expression = solveParentesis(tokens, i);
		} else {
			expression = solveToken(token);
			switch(expression->type()) {
				case ET_CONSTANT:
				case ET_SIMPLE:
					i++;
					break;	  
				case ET_BINARY:
					((BinaryExpression*)expression)->push(waitingList.back());
					waitingList.pop_back();
					i++;
					((BinaryExpression*)expression)->push(solveExpression(tokens, i));
					break;
			}
		}
		waitingList.push_back(expression);

	}

	// the last token will not be processed, this could be the last parentesis
	// or the end token, it will be processed by the caller
	//	i--;
	if (waitingList.size() == 1) {
		return waitingList.back();
	} else {
		// ERROR 
		return NULL;
	}
}

BaseExpression* createTree(std::list<Token*> tokens) {
	// process binary operators
	std::list<Token*>::iterator i = tokens.begin();
	BaseExpression* expression = solveExpression(tokens, i);

	return expression;// tokens.front();
}

void pushBuffer(std::list<Token*>& tokens, char* buffer, int& posBuffer) {
	if (strlen(buffer) > 0) {
		int tempPos = 0;
		TOKEN_TYPE type = checkTokenType(buffer, tempPos);
		if (type == TT_NOTTOKEN) {
			tokens.push_back(new Token(TT_CONSTANT, buffer));
			memset(buffer, 0, BUFFER_SIZE);
			posBuffer = 0;
		} else {
			tokens.push_back(new Token(type, buffer));
		}
	}
}

// static
FilterParser* FilterParser::parse(const std::string& expression) {
	const char* chrs = expression.c_str();

	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);
	int pos = 0;
	int posBuffer = 0;
	int len = strlen(chrs);

	TOKEN_TYPE token_type = TT_NOTTOKEN;

	std::list<Token*> tokens;
	BaseExpression* rootExpression = NULL;
	bool strOpen = false;
	char startStringChar = '\'';
	const char* VALID_CHARS = "$abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_";
	int openParentesis = 0;
	FILTER_OPERATORS lastOperator;

	while (pos < len) {
		bool charProcessed = false;
		while (!strOpen && (chrs[pos] == ' ')) {
			pos++;
		}
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
			TOKEN_TYPE type;
			if (buffer[0] == '$') {
				type = TT_EXPRESION;
			} else {
				type = TT_CONSTANT;
			}
			tokens.push_back(new Token(type, std::string(buffer)));
			memset(buffer, 0, BUFFER_SIZE);
			posBuffer = 0;
			/* 
				} else if ((!strOpen) && (chrs[pos] == '(')) {
				pushBuffer(tokens, buffer, posBuffer);
				tokens.push_back(new Token(TT_OPENPARENTESIS));
				openParentesis++;
				charProcessed = true;
				} else if ((!strOpen) && (chrs[pos] == ')')) {
				pushBuffer(tokens, buffer, posBuffer);
				tokens.push_back(new Token(TT_CLOSEPARENTESIS));
				charProcessed = true;
				openParentesis--;
				if (openParentesis < 0) {
			// ERROR
			}
			*/
		} else if (strchr(VALID_CHARS, chrs[pos]) != NULL) {
			buffer[posBuffer] = chrs[pos];
			posBuffer++;
		} else {
			pushBuffer(tokens, buffer, posBuffer);
			TOKEN_TYPE type = checkTokenType(chrs, pos);
			tokens.push_back(new Token(type, std::string(buffer)));

			if (type == TT_OPENPARENTESIS)
				openParentesis++;
			else if (type == TT_CLOSEPARENTESIS) {
				openParentesis--;
				if (openParentesis < 0) {
					// ERROR
				}
			}
			memset(buffer, 0, BUFFER_SIZE);
			posBuffer = 0;
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


