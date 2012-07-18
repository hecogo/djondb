/*
 * =====================================================================================
 *
 *       Filename:  filterdefs.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/17/2012 10:11:56 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "filterdefs.h"

FILTER_OPERATORS parseFilterOperator(const char* text) {
	FILTER_OPERATORS result = FO_NONE;
	if (compareInsensitive(text, "or")) {
		result = FO_OR;
	} else if (compareInsensitive(text, "and")) {
		result = FO_AND;
	} else if (compareInsensitive(text, "==")) {
		result = FO_EQUALS;
	}
	return result;
};


