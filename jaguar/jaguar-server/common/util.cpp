#include <string.h>

#include "util.h"
#include <stdlib.h>
#include <stdio.h>
#include <cstdarg>

int __errorCode;
char* __errorDescription;

string toString(float value) {
    stringstream ss;
    ss << value;
    return ss.str();
}

vector<string*>* listDir(string dir, string ext) {
    DIR* dirp = opendir(dir.c_str());
    vector<string*>* res = new vector<string*>();
    dirent* dirfound;
    while ((dirfound = readdir(dirp)) != NULL) {
        stringstream ssfileext;
        ssfileext << dirfound->d_name;
        string fileext = ssfileext.str();
        fileext = fileext.substr(fileext.rfind("."));
        if (fileext.compare(ext) == 0) {
            string* fileFound = new string(dirfound->d_name);
            res->push_back(fileFound);
        }
    }

    return res;
}

const char* strtrim(const char* str) {
    string response (str);
    response.erase(response.find_last_not_of(" ") + 1);
    return response.c_str();
}

void trim(string* str) {
    str->erase(str->find_last_not_of(" ") + 1);
}

void format(char* dest, char* s, ...) {
    int len = strlen(s) * 2;
    char* buffer = (char*)malloc(len);
    memset(buffer, 0, len);

    va_list ap;
    va_start(ap, s);
    int lenbuf = vsprintf(buffer, s, ap);
    va_end(ap);

    memcpy(dest, buffer, lenbuf);
    free(buffer);
}

char* nextProp(const char* source, int &index) {
    const char* n;
    char* prop = NULL;
    if ((n = strchr(source, '.')) != NULL) {
        int l = n-source;
        n = n+1;
        prop = (char*)malloc(l+1);
        memset(prop, 0, l);
        memcpy(prop, source, l);
        prop[l] = 0;
        index = l;
    } else {
        int l = strlen(source);
        prop = (char*)malloc(l+1);
        memset(prop, 0, l);
        strcpy(prop, source);
        prop[l] = 0;
        index = -1;
    }
    return prop;
}

void setLastError(int errorCode, const char* description, ...) {
    __errorCode = errorCode;

    int len = strlen(description) * 2;
    char* buffer = (char*)malloc(len);
    memset(buffer, 0, len);

    va_list ap;
    va_start(ap, description);
    int lenbuf = vsprintf(buffer, description, ap);
    va_end(ap);

    __errorDescription = (char*)malloc(lenbuf);
    memset(__errorDescription, 0, lenbuf);
    memcpy(__errorDescription, buffer, lenbuf);
    free(buffer);
}

void clearLastError() {
    __errorCode = 0;
    if (__errorDescription) {
        free(__errorDescription);
    }
    __errorDescription = NULL;
}

int getLastErrorCode() {
    return __errorCode;
}

const char* getLastErrorDescription() {
    return __errorDescription;
}

char* lastToken;

char* strtokenizer(char* str, char* delim) {
    if (str != NULL) {
        lastToken = str;
    }
    if (lastToken == NULL) {
        return NULL;
    }
    char* pointer = strstr(lastToken, delim);
    if (pointer != NULL) {
        int len = pointer - lastToken;
        char* result = (char*)malloc(len + 1);
        strncpy(result, lastToken, len);
        result[len] = 0;
        lastToken = pointer + strlen(delim);
        return result;
    } else {
        int len = strlen(lastToken);
        char* result = (char*)malloc(len + 1);
        strncpy(result, lastToken, len);
        result[len] = 0;
        lastToken = NULL;
        return result;
    }
}