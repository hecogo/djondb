/* 
 * File:   Response.cpp
 * Author: cross
 * 
 * Created on November 24, 2009, 9:33 PM
 */

#include "response.h"
#include "defs.h"
#include <string.h>

Response::Response(string* _data) {
    data = _data;
};

string* Response::getData() {
    return data;
};

void Response::addParameter(char* name, void* contents, int size) {
    if (strlen(name) > 4) {
        throw NetworkException(new string("The codename cannot be larger than 4 bytes"));
    }
    if (!data) {
        data = new string();
    }
    data->append(name, (char*)contents);
}

Response::~Response() {
    delete(data);
}

