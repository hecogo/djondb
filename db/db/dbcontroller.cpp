#include "dbcontroller.h"
#include "bson.h"
#include "util.h"
#include "fileinputoutputstream.h"
#include "fileinputstream.h"
#include "fileoutputstream.h"

#include "bsonoutputstream.h"
#include "bsoninputstream.h"

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
    std::auto_ptr<FileOutputStream> fos(new FileOutputStream("djondb.dat", "wb"));
    for (std::map<std::string, SpacesType>::iterator i = _spaces.begin(); i != _spaces.end(); i++) {
        SpacesType space = i->second;
        std::string ns = space.ns;
        FILE_TYPE type = space.type;
        fos->writeString(ns);
        fos->writeInt(static_cast<int>(type));
        space.stream->close();
    }
    fos->close();
}

void DBController::initialize() {
    std::auto_ptr<FileInputStream> fis(new FileInputStream("djondb.dat", "rb"));
    while (!fis->eof()) {
        std::auto_ptr<std::string> ns(fis->readString());
        FILE_TYPE type = static_cast<FILE_TYPE>(fis->readInt());

        StreamType* stream = open(*(ns.get()), type);
        long currentPos = stream->currentPos();
        if (type == INDEX_FTYPE) {
            stream->seek(0);
            IndexAlgorithm* impl = NULL;
            while (!stream->eof()) {
                BSONObj* obj = readBSON(stream);

                if (!impl) {
                    impl = IndexFactory::indexFactory.index(ns->c_str(), *obj);
                }
                long indexPos = stream->readLong();
                long posData = stream->readLong();
                Index* index = impl->add(*obj, posData);
                index->indexPos = indexPos;
                delete obj;
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
    auto_ptr<BSONOutputStream> out(new BSONOutputStream(stream));
    out->writeBSON(*obj);
}

BSONObj* DBController::readBSON(StreamType* stream) {
    auto_ptr<BSONInputStream> is(new BSONInputStream(stream));
    BSONObj* res = is->readBSON();
    return res;
}

BSONObj* DBController::insert(char* ns, BSONObj* obj) {
    Logger* log = getLogger(NULL);
    StreamType* streamData = open(std::string(ns), DATA_FTYPE);

    BSONObj* result = NULL;
    if (!obj->has("_id")) {
        string* tid = uuid();
        std::string key("_id");
        obj->add(key, *tid);
        result = new BSONObj();
        result->add("_id", *tid);
        delete tid;
    }

    std::string* id = NULL;
    if (obj->type("_id") == STRING_TYPE) {
        id = obj->getString("_id");
    } else if (obj->type("_id") == PTRCHAR_TYPE) {
        id = new std::string(obj->getChars("_id"));
    }
//    long crcStructure = checkStructure(obj);

//    char* text = obj->toChar();
//    streamData->writeChars(text, strlen(text));
//    free(text);

    insertIndex(ns, obj, streamData->currentPos());

    writeBSON(streamData, obj);

    if (id != NULL) {
        CacheManager::objectCache()->add(*id, new BSONObj(*obj));
    }

    delete log;
    return result;
}

void DBController::update(char* ns, BSONObj* obj) {
    Logger* log = getLogger(NULL);
    StreamType* streamData = open(std::string(ns), DATA_FTYPE);

//    long crcStructure = checkStructure(obj);

//    char* text = obj->toChar();
//    streamData->writeChars(text, strlen(text));
//    free(text);

    updateIndex(ns, obj, streamData->currentPos());

    writeBSON(streamData, obj);

    std::string* id = obj->getString("_id");

    CacheManager::objectCache()->add(*id, new BSONObj(*obj));
    delete log;
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
    BSONObj indexBSON;
    indexBSON.add("_id", *bson->getString("_id"));
    IndexAlgorithm* impl = IndexFactory::indexFactory.index(ns, indexBSON);
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
    BSONObj indexBSON;
    std::string* id = bson->getString("_id");
    indexBSON.add("_id", *id);
    IndexAlgorithm* impl = IndexFactory::indexFactory.index(ns, indexBSON);
    Index* index = impl->add(indexBSON, filePos);

    StreamType* out = open(std::string(ns), INDEX_FTYPE);
    index->indexPos = out->currentPos();
    BSONObj* key = index->key;
    writeBSON(out, key);
    out->writeLong(index->indexPos);
    out->writeLong(index->posData);
}

std::vector<BSONObj*> DBController::find(char* ns, const BSONObj& filter) {
    std::string* id = filter.getString("_id");

    BSONObj indexBSON;
    indexBSON.add("_id", *id);
    IndexAlgorithm* impl = IndexFactory::indexFactory.index(ns, indexBSON);
    Index* index = impl->find(indexBSON);

    std::vector<BSONObj*> result;
    if (index != NULL) {
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
        result.push_back(obj);
        input->close();
    }
    return result;
}

BSONObj* DBController::findFirst(char* ns, BSONObj* filter) {
    std::string* id = filter->getString("_id");
    if (CacheManager::objectCache()->containsKey(*id)) {
        return (*CacheManager::objectCache())[*id];
    }
    std::vector<BSONObj*> temp = find(ns, *filter);
    if (temp.size() == 1) {
        BSONObj* element = *temp.begin();
        CacheManager::objectCache()->add(*id, new BSONObj(*element));
        return element;
    } else {
        return NULL;
    }
}

