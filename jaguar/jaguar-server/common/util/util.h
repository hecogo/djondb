#include <string>
#include <sstream>
#include <dirent.h>
#include <vector>
#include "logger/logger.h"
#include "cache.h"
#include "threads.h"
#include "timerecord.h"
#include <typeinfo>

using namespace std;

string toString(float value);

vector<string*>* listDir(string dir, string ext);

const char* strtrim(char* str);

void trim(string* str);
