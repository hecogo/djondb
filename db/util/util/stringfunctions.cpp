#include "stringfunctions.h"
#include "../util.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <sstream>

char* strcpy(std::string str) {
    return strcpy(const_cast<char*>(str.c_str()), str.length());
}

char* strcpy(char* str, int len) {
    char* result = (char*)malloc(len + 1);
    memset(result, 0, len +1);
    memcpy(result, str, len);
    return result;
}

bool endsWith(char* source, char* check) {
    if (strlen(source) < strlen(check)) {
        return false;
    }
    char* test = source + (strlen(source) - strlen(check));
    if (strcmp(test, check) == 0) {
        return true;
    } else {
        return false;
    }
}

std::vector<std::string*>* tokenizer(const std::string source, const char* tokens) {
    std::vector<std::string*>* result = new std::vector<std::string*>();
    char* csource = strcpy(source);
    char* token = strtok(csource, tokens);
    while (token != NULL) {
        std::string* item = new std::string(token);
        result->push_back(item);
        token = strtok(NULL, tokens);
    }
    free(csource);

    return result;
}

std::string format(const char * fmt, ...) {
  char* buffer = (char*)malloc(1000);
  memset(buffer, 0, 1000);
  va_list args;
  va_start (args, fmt);
  vsprintf (buffer,fmt, args);
  va_end(args);
  std::string result;
  std::stringstream ss;
  ss << buffer;
  result = ss.str();
  free(buffer);
  return result;
}

std::string toString(double a) {
    std::stringstream ss;

    ss << a;
    string res = ss.str();
    return res;
}

std::string toString(double a, int fixedPrecision) {
    std::stringstream ss;

    ss.precision(fixedPrecision);
    ss.setf(ios::fixed,ios::floatfield);

    ss << a;
    string res = ss.str();
    return res;
}

std::string toString(int a) {
    std::stringstream ss;
    ss << a;
    string s = ss.str();
    return s;
}

bool endsWith(const char* text, const char* end) {
    if (strlen(end) > strlen(text)) {
        return false;
    }
    for (unsigned int pos = 0; strlen(end) > pos; pos++) {
        if (end[strlen(end) - pos] != text[strlen(text) - pos]) {
            return false;
        }
    }
    return true;
}

std::vector<string> split(const string str, string token) {
//    char* s = (char*) malloc(str.size());
    const char* delim = token.c_str();

    //strcpy(s, str.c_str());
    char* s = strcpy((char*)str.c_str());

    vector<string> res;
    char* ptr;
    ptr = strtok(s, delim);
    while (ptr != NULL) {
        res.push_back(string(ptr));
        ptr = strtok(NULL, delim);
    }

    free (s);
    return res;
}


long countChar(const char* s, const char c) {
    long num = 0;
    for (unsigned int x = 0; x < strlen(s); x++) {
        if (s[x] == c) {
            num++;
        }
    }
    return num;
}

