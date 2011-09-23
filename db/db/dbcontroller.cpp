#include "dbcontroller.h"
#include "bson.h"
#include "util.h"
#include "fileoutputstream.h"
#include "fileinputstream.h"
#include "cachemanager.h"
#include "indexfactory.h"
#include "index.h"
#include <memory>
#include <iostream>
#include <sstream>
#include <string.h>

using namespace std;

DBController::DBController()
{
}

DBController::~DBController()
{
    for (std::map<std::string, FileOutputStream*>::iterator i = _spaces.begin(); i != _spaces.end(); i++) {
        FileOutputStream* stream = i->second;
        stream->close();
        delete(stream);
        stream = 0;
    }
}

void DBController::shutdown() {
}

void DBController::initialize() {
    FileInputStream* fis = new FileInputStream("jaguar.dat", "rb");
    while (fis->eof()) {
        std::string* ns = fis->readString();

        IndexAlgorithm* impl = IndexFactory::indexFactory->index(ns, indexBSON);
        FileInputStream* fis = new FileInputStream(*ns + ".idx");
        while (fis->eof()) {
            BSONObj* obj = readBSON(fis);
            long indexPos = index->indexPos);
            long posData = index->posData;
            Index* index = impl->add(obj, posData);
            index->indexPos = indexPos;
        }
        fis->close();
    }
    fis->close();
}

long DBController::checkStructure(BSONObj* obj) {
    Structure* structure = new Structure();
    for (std::map<t_keytype, BSONContent* >::const_iterator i = obj->begin(); i != obj->end(); i++) {
        structure->add(i->first);
    }

    StructureCache* cache = CacheManager::structuresCache();
    long strId = structure->crc();
    if (!cache->containsKey(strId)) {
        cache->add(strId, structure);
    } else {
        delete(structure);
    }
    return strId;
}

void DBController::writeBSON(FileOutputStream* stream, BSONObj* obj) {

    stream->writeInt(obj->length());
    for (std::map<t_keytype, BSONContent*>::const_iterator i = obj->begin(); i != obj->end(); i++) {
        t_keytype key = i->first;
        stream->writeString(&key);
        BSONContent* cont = i->second;
        stream->writeInt(cont->_type);
        char* text;
        switch (cont->_type) {
            case BSON_TYPE:
                // Unsupported yet;
                break;
            case INT_TYPE:
                stream->writeInt(*((int*)cont->_element));
                break;
            case LONG_TYPE:
                stream->writeLong(*((long*)cont->_element));
                break;
            case DOUBLE_TYPE:
                stream->writeDoubleIEEE(*((double*)cont->_element));
                break;
            case PTRCHAR_TYPE:
                text = (char*)cont->_element;
                stream->writeChars(text, strlen(text));
                break;
            case STRING_TYPE:
                string* str = (string*)cont->_element;
                stream->writeString(str);
                break;
        }
    }
}

BSONObj* DBController::readBSON(FileInputStream* stream) {

    BSONObj* obj = new BSONObj();
    int elements = stream->readInt();
    for (int x = 0; x < elements; x++) {
        string key = *stream->readString();

        int type = stream->readInt();
        char* text;
        switch (type) {
            case BSON_TYPE:
                // Unsupported yet;
                break;
            case INT_TYPE:
                obj->add(key, stream->readInt());
                break;
            case LONG_TYPE:
                obj->add(key, stream->readLong());
                break;
            case DOUBLE_TYPE:
                obj->add(key, stream->readDoubleIEEE());
                break;
            case PTRCHAR_TYPE:
                obj->add(key, stream->readChars());
                break;
            case STRING_TYPE:
                obj->add(key, stream->readString());
                break;
        }
    }
    return obj;
}

void DBController::insert(char* ns, BSONObj* obj) {
    FileOutputStream* streamData = open(ns, DATA_FTYPE);

    std::string* id = obj->getString("_id");
    if (id == NULL) {
        id = uuid();
        obj->add("_id", id);
    }

    long crcStructure = checkStructure(obj);

//    char* text = obj->toChar();
//    streamData->writeChars(text, strlen(text));
//    free(text);

    updateIndex(ns, obj, streamData->currentPos());

    writeBSON(streamData, obj);
//    stream->flush();
}


FileOutputStream* DBController::open(char* ns, FILE_TYPE type) {

    std::stringstream ss;
    ss << ns << ".";
    switch (type) {
        case DATA_FTYPE:
            ss << "dat";
            break;
        case INDEX_FTYPE:
            ss << "idx";
            break;
        case STRC_FTYPE:
            ss << "stt";
            break;
    }

    std::string fileName = ss.str();
    FileOutputStream* stream = NULL;
    for (map<std::string, FileOutputStream*>::iterator it = _spaces.begin(); it != _spaces.end(); it++) {
        std::string key = it->first;
        if (key.compare(fileName) == 0) {
            stream = it->second;
            break;
        }
//        if (stream->currentPos() < (300 * 1024 * 1024)) {
//        } else {
//            fileName = (char*)stream->fileName();
//            stream->close();
//            delete(stream);
//            char* newFileName = (char*)malloc(strlen(fileName) + 2);
//            memset(newFileName, 0, strlen(fileName) + 2);
//            strcat(newFileName, fileName);
//            strcat(newFileName, "1");
//            fileName = newFileName;
//            _spaces.erase(it);
//        }
    }
    if (stream != NULL) {
        return stream;
    }
    FileOutputStream* output = new FileOutputStream(const_cast<char*>(fileName.c_str()), "ab+");
    _spaces.insert(pair<std::string, FileOutputStream*>(fileName, output));
    return output;
}

bool DBController::close(char* ns) {
    map<std::string, FileOutputStream*>::iterator it = _spaces.find(std::string(ns));
    if (it != _spaces.end()) {
        FileOutputStream* stream = it->second;
        stream->close();
        delete(stream);
        stream = 0;
        _spaces.erase(it);
    }
    return true;
}

void DBController::updateIndex(char* ns, BSONObj* bson, long filePos) {
    BSONObj* indexBSON = new BSONObj();
    indexBSON->add("_id", bson->getString("_id"));
    IndexAlgorithm* impl = IndexFactory::indexFactory->index(ns, indexBSON);
    Index* index = impl->find(indexBSON);

    index->pos = filePos;

    FileOutputStream* out = open(ns, INDEX_FTYPE);
    long currentPos = out->currentPos();
    out->seek(index->indexPos);
    BSONObj* key = index->key;
    writeBSON(out, key);
    out->writeLong(index->indexPos);
    out->writeLong(index->posData);
    out->seek(currentPos);
}

void DBController::insertIndex(char* ns, BSONObj* bson, long filePos) {
    BSONObj* indexBSON = new BSONObj();
    indexBSON->add("_id", bson->getString("_id"));
    IndexAlgorithm* impl = IndexFactory::indexFactory->index(ns, indexBSON);
    Index* index = impl->find(indexBSON);

    index->posData = filePos;

    FileOutputStream* out = open(ns, INDEX_FTYPE);
    index->indexPos = out->currentPos();
    BSONObj* key = index->key;
    writeBSON(out, key);
    out->writeLong(index->indexPos);
    out->writeLong(index->posData);
}

std::vector<BSONObj*> DBController::find(char* ns, BSONObj* filter) {
    BSONObj* indexBSON = new BSONObj();
    indexBSON->add("_id", filter->getString("_id"));
    IndexAlgorithm* impl = IndexFactory::indexFactory->index(ns, indexBSON);
    Index* index = impl->find(indexBSON);

    char fileName[255];
    memset(fileName, 0, 255);
    strcat(fileName, ns);
    strcat(fileName, ".");
    strcat(fileName, "dat");

    FileOutputStream* out = open(ns, DATA_FTYPE);
    out->flush();
//    out->close();

    FileInputStream* input = new FileInputStream(fileName, "rb");
    input->seek(index->pos);

    BSONObj* obj = readBSON(input);
    std::vector<BSONObj*> result;
    result.push_back(obj);
    input->close();

    return result;
}

BSONObj* DBController::findFirst(char* ns, BSONObj* filter) {
    std::vector<BSONObj*> temp = find(ns, filter);
    if (temp.size() == 1) {
        return *temp.begin();
    } else {
        return NULL;
    }
}
