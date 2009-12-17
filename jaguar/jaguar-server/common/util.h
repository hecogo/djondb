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

const char* strtrim(char* str);

void trim(string* str);

void format(char* dest, char* s, ...);