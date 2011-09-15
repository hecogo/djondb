#include "dbcontroller.h"
#include "bson.h"
#include "util.h"
#include "fileoutputstream.h"
#include <iostream>
#include <string.h>
#include "cachemanager.h"

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

long DBController::checkStructure(BSONObj* obj) {
    Structure* structure = new Structure();
    for (std::map<char*, BSONContent* >::const_iterator i = obj->begin(); i != obj->end(); i++) {
        structure->add(i->first);
    }

    StructureCache* cache = CacheManager::structuresCache();
    long strId = structure->crc();
    if (!cache->containsKey(strId)) {
        cache->add(strId, structure);
    }
}

void DBController::insert(char* ns, BSONObj* obj) {
    FileOutputStream* streamData = open(ns, DATA_FTYPE);

    std::string* id = obj->getString("_id");
    if (id == NULL) {
        obj->add("_id", uuid());
    }

    long crcStructure = checkStructure(obj);

//    char* text = obj->toChar();
//    streamData->writeChars(text, strlen(text));
//    free(text);
    streamData->writeInt(obj->length());
    for (std::map<char*, BSONContent*>::const_iterator i = obj->begin(); i != obj->end(); i++) {
        char* key = i->first;
        streamData->writeChars(key, strlen(key));
        BSONContent* cont = i->second;
        streamData->writeInt(cont->_type);
        char* text;
        switch (cont->_type) {
            case BSON_TYPE:
                // Unsupported yet;
                break;
            case INT_TYPE:
                streamData->writeInt(*((int*)cont->_element));
                break;
            case LONG_TYPE:
                streamData->writeLong(*((long*)cont->_element));
                break;
            case DOUBLE_TYPE:
                streamData->writeDoubleIEEE(*((double*)cont->_element));
                break;
            case PTRCHAR_TYPE:
                text = (char*)cont->_element;
                streamData->writeChars(text, strlen(text));
                break;
            case STRING_TYPE:
                string* str = (string*)cont->_element;
                streamData->writeString(str);
                break;
        }
    }
//    stream->flush();
}


FileOutputStream* DBController::open(char* ns, FILE_TYPE type) {
    char* fileName = (char*)malloc(strlen(ns) + 5);
    memset(fileName, 0, strlen(ns) + 5);
    strcat(fileName, ns);
    strcat(fileName, ".");
    switch (type) {
        case DATA_FTYPE:
            fileName = strcat(fileName, "dat");
            break;
        case STRC_FTYPE:
            fileName = strcat(fileName, "stc");
            break;
    }

    map<char*, FileOutputStream*>::iterator it = _spaces.find(ns);
    fileName = ns;
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

