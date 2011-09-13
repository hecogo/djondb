#include "dbcontroller.h"
#include "bson.h"
#include <fileoutputstream.h>
#include <iostream>
#include <string.h>
#include "util.h"

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

    std::string* id = obj->getString("_id");
    if (id == NULL) {
        id = uuid();
        obj->add("_id", *id);
    }
    char* c = obj->toChar();
    stream->writeChars(c, strlen(c));
    free(c);
//    stream->flush();
}


FileOutputStream* DBController::open(char* ns) {
    map<char*, FileOutputStream*>::iterator it = _spaces.find(ns);
    char* fileName = ns;
    if (it != _spaces.end()) {
        FileOutputStream* stream = it->second;
        if (stream->currentPos() < (300 * 1024 * 1024)) {
            return stream;
        } else {
            fileName = (char*)stream->fileName();
            stream->close();
            delete(stream);
            char* newFileName = (char*)malloc(strlen(fileName) + 2);
            memset(newFileName, 0, strlen(fileName) + 2);
            strcat(newFileName, fileName);
            strcat(newFileName, "1");
            fileName = newFileName;
            _spaces.erase(it);
        }
    }
    FileOutputStream* output = new FileOutputStream(fileName, "ab+");
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



