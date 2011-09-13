#include "dbcontroller.h"
#include "bson.h"
#include <fileoutputstream.h>
#include <iostream>
#include <string.h>

using namespace std;

DBController::DBController()
{
}

DBController::~DBController()
{
    for (std::map<char*, FileOutputStream*>::iterator i = _spaces.begin(); i != _spaces.end(); i++) {
        FileOutputStream* stream = i->second;
        stream->close();
        delete(stream);
        stream = 0;
    }
}

void DBController::insert(char* ns, BSONObj* obj) {
    FileOutputStream* stream = open(ns);

    char* c = obj->toChar();
    stream->writeChars(c, strlen(c));
    free(c);
}


FileOutputStream* DBController::open(char* ns) {
    map<char*, FileOutputStream*>::iterator it = _spaces.find(ns);
    if (it != _spaces.end()) {
        return it->second;
    }
    FileOutputStream* output = new FileOutputStream(ns, "ab+");
    _spaces.insert(pair<char*, FileOutputStream*>(ns, output));
    return output;
}

bool DBController::close(char* ns) {
    map<char*, FileOutputStream*>::iterator it = _spaces.find(ns);
    if (it != _spaces.end()) {
        FileOutputStream* stream = it->second;
        stream->close();
        delete(stream);
        stream = 0;
        _spaces.erase(it);
    }
    return true;
}



