#include "dbcontroller.h"
#include "bson.h"
#include "util.h"
#include "fileinputoutputstream.h"
#include "fileinputstream.h"
#include "fileoutputstream.h"
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
}

void DBController::shutdown() {
    FileOutputStream* fos = new FileOutputStream("djondb.dat", "wb");
    for (std::map<std::string, SpacesType>::iterator i = _spaces.begin(); i != _spaces.end(); i++) {
        SpacesType space = i->second;
        std::string ns = space.ns;
        FILE_TYPE type = space.type;
        fos->writeString(&ns);
        fos->writeInt(static_cast<int>(type));
        space.stream->close();
    }
    fos->close();
}

void DBController::initialize() {
    FileInputStream* fis = new FileInputStream("djondb.dat", "rb");
    while (!fis->eof()) {
        std::string* ns = fis->readString();
        FILE_TYPE type = static_cast<FILE_TYPE>(fis->readInt());

        StreamType* stream = open(*ns, type);
        long currentPos = stream->currentPos();
        if (type == INDEX_FTYPE) {
            stream->seek(0);
            IndexAlgorithm* impl = NULL;
            while (!stream->eof()) {
                BSONObj* obj = readBSON(stream);

                if (!impl) {
                    impl = IndexFactory::indexFactory->index(ns->c_str(), obj);
                }
                long indexPos = stream->readLong();
                long posData = stream->readLong();
                Index* index = impl->add(obj, posData);
                index->indexPos = indexPos;
            }
            stream->seek(currentPos);
        }
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

void DBController::writeBSON(StreamType* stream, BSONObj* obj) {

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

BSONObj* DBController::readBSON(StreamType* stream) {

    BSONObj* obj = new BSONObj();
    int elements = stream->readInt();
    for (int x = 0; x < elements; x++) {
        string key = *stream->readString();

        int type = stream->readInt();
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
    StreamType* streamData = open(ns, DATA_FTYPE);

    std::string* id = obj->getString("_id");
    if (id == NULL) {
        id = uuid();
        obj->add("_id", id);
    }

    long crcStructure = checkStructure(obj);

//    char* text = obj->toChar();
//    streamData->writeChars(text, strlen(text));
//    free(text);

    insertIndex(ns, obj, streamData->currentPos());

    writeBSON(streamData, obj);
//    stream->flush();
}


StreamType* DBController::open(std::string ns, FILE_TYPE type) {

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
    StreamType* stream = NULL;
    for (map<std::string, SpacesType>::iterator it = _spaces.begin(); it != _spaces.end(); it++) {
        std::string key = it->first;
        if (key.compare(fileName) == 0) {
            SpacesType space = it->second;
            stream = space.stream;
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
    StreamType* output = new StreamType(fileName, "ab+");
    SpacesType space;
    space.ns = ns;
    space.stream = output;
    space.type = type;
    _spaces.insert(pair<std::string, SpacesType>(fileName, space));
    return output;
}

bool DBController::close(char* ns) {
    map<std::string, SpacesType>::iterator it = _spaces.find(std::string(ns));
    if (it != _spaces.end()) {
        SpacesType space = it->second;

        StreamType* stream = space.stream;
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

    index->posData = filePos;

    StreamType* out = open(ns, INDEX_FTYPE);
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

    StreamType* out = open(ns, INDEX_FTYPE);
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

    StreamType* out = open(ns, DATA_FTYPE);
    out->flush();
//    out->close();

    StreamType* input = new StreamType(fileName, "rb");
    input->seek(index->posData);

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
