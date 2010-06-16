#ifndef _UTIL_H
#define	_UTIL_H

#include <string>
#include <sstream>
#include <dirent.h>
#include <vector>
#include "util/logger/logger.h"
#include "util/cache.h"
#include "util/threads.h"
#include "util/timerecord.h"
#include <typeinfo>

using namespace std;

string toString(float value);

vector<string*>* listDir(string dir, string ext);

const char* strtrim(const char* str);

void trim(string* str);

/* strtok with a fixed delimeter, it will use the full delim param to search */
char* strtokenizer(char* str, char* delim);

void format(char* dest, char* s, ...);

/**
 * Returns the next section of an xpath and the index of the separator found
 *
 * The caller should free the returned pointer
 * 
 * Usage:
 * 
 * char* source = "test.a[x].test2.test3";
 * char* dest;
 * while (true) {
 *   int index = -1;
 *   dest = nextProp(source, index);
 *   printf("prop: %s\n", dest);
 *   free(dest);
 *   if (index == -1) {
 *       break;
 *   }
 *   source = source + index + 1;
 * };
 *
 **/
char* nextProp(const char* source, int &index);

/***************************************************************************/
// Error Managment
/***************************************************************************/
void setLastError(int errorCode, const char* description, ...);
void clearLastError();
int getLastErrorCode();
const char* getLastErrorDescription();
#endif	/* _UTIL_H */
