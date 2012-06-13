/*
 * File:   util.h
 * Author: cross
 *
 * Created on July 7, 2010, 1:33 PM
 */

#ifndef _UTIL_H
#define	_UTIL_H

#include "util/DateTime.h"
#include "util/dtime.h"
#include "util/fileutil.h"
#include "util/stringfunctions.h"
#include "util/errorHandle.h"
#include "util/version.h"
#include "util/logger.h"
#include "util/threads.h"
#include "util/settings.h"

#include <string>
#include <vector>
#include <map>

/*****************************************************************
  Type Definitions and macros
*/

bool isDaemon();
void setDaemon(bool daemon);

void logInfo(char* text);

long idleTime();

bool endsWith(const char* text, const char* end);

std::string* uuid();

bool makedir(const char* path);
std::string* getHomeDir();
std::string* getTempDir();

Version getCurrentVersion();
Version getVersion(const char* version);

/***********************************************************************
* Memory functions
***********************************************************************/
void* mmalloc(size_t size);

/***********************************************************************/

#endif	/* _UTIL_H */

