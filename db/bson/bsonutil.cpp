/*
 * =====================================================================================
 *
 *       Filename:  bsonutil.cpp
 *
 *    Description:  This contains utility functions for bson
 *
 *        Version:  1.0
 *        Created:  09/09/2012 07:22:40 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Juan Pablo Crossley (crossleyjuan@gmail.com), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "bsonutil.h"

std::set<std::string> bson_splitSelect(const char* select) {
	std::vector<std::string> elements = split(std::string(select), ",");

	std::set<std::string> result;
	for (std::vector<std::string>::const_iterator i = elements.begin(); i != elements.end(); i++) {
		std::string s = *i;
		char* cs = trim(const_cast<char*>(s.c_str()), s.length());
		if (startsWith(cs, "$")) {
			s = std::string(std::string(cs), 2, strlen(cs) - 3);
		} else {
			s = std::string(cs);
		}
		int dotPos = s.find('.');
		if (dotPos != string::npos) {
			s = s.substr(0, dotPos);
		}
		result.insert(s);
	}

	return result;
}

char* bson_subselect(const char* select, const char* name) {
	std::set<std::string> elements = splitSelect(select);
	MemoryStream ms(2048);

	std::string startXpath = format("%s.", name);
	int lenStartXpath = startXpath.length();
	bool first = true;
	for (std::set<std::string>::const_iterator i = elements.begin(); i != elements.end(); i++) {
		std::string selement = *i;
		char* element = const_cast<char*>(selement.c_str());
		element = trim(element, strlen(element));
		if (startsWith(element, "$")) {
			// Remvoes the $" " from the element
			element = strcpy(element, 2, strlen(element) - 3);
			if (startsWith(element, startXpath.c_str())) {
				char* suffix = strcpy(element, lenStartXpath, strlen(element) - lenStartXpath);
				ms.writeChars(suffix, strlen(suffix));
				if (!first) {
					ms.writeChars(", ", 2);
				}
				first = false;
				free(suffix);
			}
		}
	}
}
