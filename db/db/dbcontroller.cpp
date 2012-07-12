// *********************************************************************************************************************
// file:
// author: Juan Pablo Crossley (crossleyjuan@gmail.com)
// created:
// updated:
// license:
// 
// This file is part of the djondb project, for license information please refer to the LICENSE file,
// the application and libraries are provided as-is and free of use under the terms explained in the file LICENSE
// Its authors create this application in order to make the world a better place to live, but you should use it on
// your own risks.
// 
// Also, be adviced that, the GPL license force the committers to ensure this application will be free of use, thus
// if you do any modification you will be required to provide it for free unless you use it for personal use (you may 
// charge yourself if you want), bare in mind that you will be required to provide a copy of the license terms that ensures
// this program will be open sourced and all its derivated work will be too.
// *********************************************************************************************************************

#include "dbcontroller.h"
#include "bson.h"
#include "util.h"
#include "fileinputoutputstream.h"
#include "fileinputstream.h"
#include "fileoutputstream.h"

#include "bsonoutputstream.h"
#include "bsoninputstream.h"
#include "filterparser.h"

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
	_logger = getLogger(NULL);
}

DBController::~DBController()
{
	delete _logger;
}

void DBController::shutdown() {
	if (_logger->isInfo()) _logger->info("DBController shutting down");
	saveDatabases();
	clearCache();
}

void DBController::clearCache() {
	if (_logger->isInfo()) _logger->info("DBController::clearCache");
	for (ObjectCache::iterator i = CacheManager::objectCache()->begin(); i != CacheManager::objectCache()->end(); i++) {
		BSONObj* item = i->second;
		delete item;
	}
	CacheManager::objectCache()->clear();

	for (StructureCache::iterator i = CacheManager::structuresCache()->begin(); i != CacheManager::structuresCache()->end(); i++) {
		Structure* item = i->second;
		delete item;
	}
	CacheManager::structuresCache()->clear();

}

void DBController::saveDatabases() {
	if (_logger->isInfo()) _logger->debug(2, "DBController::saveDatabases");

	if (!_initialized) {
		return;
	}
	std::auto_ptr<FileOutputStream> fos(new FileOutputStream(const_cast<char*>( (_dataDir + "djondb.dat").c_str()), "wb"));
	for (std::map<std::string, std::map<std::string, SpacesType>* >::iterator idb = _spaces.begin(); idb != _spaces.end(); idb++) {
		std::string db = idb->first;
		std::map<std::string, SpacesType>* spaces = idb->second;
		for (std::map<std::string, SpacesType>::iterator i = spaces->begin(); i != spaces->end(); i++) {
			SpacesType space = i->second;
			std::string ns = space.ns;
			fos->writeString(db);
			fos->writeString(ns);
			fos->writeInt(space.streams->size());
			for (std::map<FILE_TYPE, StreamType*>::iterator istream = space.streams->begin(); istream != space.streams->end(); istream++) {
				FILE_TYPE type = istream->first;
				fos->writeInt(static_cast<int>(type));
				StreamType* stream = istream->second;
				stream->close();
			}
			delete space.streams;
		}
		delete spaces;
	}
	fos->close();
}

void DBController::initialize() {
	std::string dataDir = getSetting("DATA_DIR");
	if ((dataDir.length() > 0) && !endsWith(dataDir.c_str(), FILESEPARATOR)) {
		dataDir = dataDir + FILESEPARATOR;
	} else {
		dataDir = dataDir;
	}

	initialize(dataDir);
	_initialized = true;
}

void DBController::initialize(std::string dataDir) {
	if (_logger->isInfo()) _logger->info("DBController initializing. Data dir");

	_dataDir = dataDir;

	if (_logger->isDebug()) _logger->debug(0, "data dir = %s", _dataDir.c_str());

	if (!existDir(_dataDir.c_str())) {
		makeDir(_dataDir.c_str());
	}

	if (!checkFileCreation(_dataDir.c_str())) {
		_logger->error("An error ocurred using the data folder: %s. Please check that the user has permissions for writing over that directory. Error: %s", _dataDir.c_str(), lastErrorDescription()); 
		exit(1);
	}

	std::auto_ptr<FileInputStream> fis(new FileInputStream((_dataDir + "djondb.dat").c_str(), "rb"));
	while (!fis->eof()) {
		std::auto_ptr<std::string> db(fis->readString());
		std::auto_ptr<std::string> ns(fis->readString());
		int streams = fis->readInt();
		for (int x = 0; x < streams; x++) {
			FILE_TYPE type = static_cast<FILE_TYPE>(fis->readInt());
			StreamType* stream = open(*(db.get()), *(ns.get()), type);

			if (type == INDEX_FTYPE) {
				long currentPos = stream->currentPos();
				stream->seek(0);
				IndexAlgorithm* impl = NULL;
				while (!stream->eof()) {
					BSONObj* obj = readBSON(stream);

					if (!impl) {
						impl = IndexFactory::indexFactory.index(db->c_str(), ns->c_str(), *obj);
					}
					long indexPos = stream->readLong();
					long posData = stream->readLong();
					impl->add(*obj, posData, indexPos);
					delete obj;
				}
				stream->seek(currentPos);
			}
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
	if (_logger->isDebug()) _logger->debug(3, "DBController is writing bson to disc: %s", obj->toChar());

	auto_ptr<BSONOutputStream> out(new BSONOutputStream(stream));
	out->writeBSON(*obj);
	stream->flush();
}

BSONObj* DBController::readBSON(StreamType* stream) {
	auto_ptr<BSONInputStream> is(new BSONInputStream(stream));
	BSONObj* res = is->readBSON();
	if (_logger->isDebug()) _logger->debug(3, "DBController read bson from disc: %s", res->toChar());
	return res;
}

BSONObj* DBController::insert(char* db, char* ns, BSONObj* obj) {
	if (_logger->isDebug()) _logger->debug(2, "DBController::insert ns: %s, bson: %s", ns, obj->toChar());
	std::string sdb(db);
	std::string sns(ns);
	StreamType* streamData = open(sdb, sns, DATA_FTYPE);

	BSONObj* result = NULL;
	if (!obj->has("_id")) {
		if (_logger->isDebug()) _logger->debug(2, "BSON does not contain an id, DBController is creating one");
		string* tid = uuid();
		std::string key("_id");
		obj->add(key, *tid);
		result = new BSONObj();
		result->add("_id", *tid);
		delete tid;
	}

	std::string id;
	if (obj->type("_id") == STRING_TYPE) {
		id = obj->getString("_id");
	} else if (obj->type("_id") == PTRCHAR_TYPE) {
		id = std::string(obj->getChars("_id"));
	}
	assert(id.length() > 0);
	//    long crcStructure = checkStructure(obj);

	//    char* text = obj->toChar();
	//    streamData->writeChars(text, strlen(text));
	//    free(text);

	insertIndex(db, ns, obj, streamData->currentPos());

	writeBSON(streamData, obj);

	//CacheManager::objectCache()->add(id, new BSONObj(*obj));

	return result;
}

void DBController::update(char* db, char* ns, BSONObj* obj) {
	if (_logger->isDebug()) _logger->debug(2, "DBController::update ns: %s, bson: %s", ns, obj->toChar());
	StreamType* streamData = open(std::string(db), std::string(ns), DATA_FTYPE);

	//    long crcStructure = checkStructure(obj);

	//    char* text = obj->toChar();
	//    streamData->writeChars(text, strlen(text));
	//    free(text);

	updateIndex(db, ns, obj, streamData->currentPos());

	writeBSON(streamData, obj);

	std::string id = obj->getString("_id");

	CacheManager::objectCache()->add(id, new BSONObj(*obj));
}

std::string DBController::fileName(std::string ns, FILE_TYPE type) const {
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

	return fileName;
}

StreamType* DBController::open(std::string db, std::string ns, FILE_TYPE type) {
	std::auto_ptr<Logger> log(getLogger(NULL));
	StreamType* stream = NULL;

	map<std::string, SpacesType>* spaces = NULL;
	map<std::string, map<std::string, SpacesType>* >::iterator itDB = _spaces.find(db);
	if (itDB == _spaces.end()) {
		spaces = new map<std::string, SpacesType>();
		_spaces.insert(pair<std::string, map<std::string, SpacesType>* >(db, spaces));
	} else {
		spaces = itDB->second;
	}

	map<std::string, SpacesType>::iterator it = spaces->find(ns);

	map<FILE_TYPE, StreamType*>* streams = NULL;
	if (it != spaces->end()) {
		streams = (it->second).streams;
		map<FILE_TYPE, StreamType*>::iterator istreams = streams->find(type);
		if (istreams != streams->end()) {
			stream = istreams->second;
		}
	} 

	if (stream != NULL) {
		return stream;
	}

	std::string filedir = concatStrings(_dataDir, db);
	filedir += FILESEPARATOR;
	if (log->isDebug()) log->debug(3, "DBController::open checking directory %s", filedir.c_str());
	if (!existDir(filedir.c_str())) {
		if (log->isDebug()) log->debug(3, "DBController::open creating directory %s", filedir.c_str());
		makeDir(filedir.c_str());
	}
	std::string file = fileName(ns, type);
	std::string streamfile = concatStrings(filedir, file);
	StreamType* output = new StreamType(streamfile, "ab+");
	if (streams) {
		streams->insert(pair<FILE_TYPE, StreamType*>(type, output));
	} else {
		SpacesType space;
		space.ns = ns;
		space.streams = new map<FILE_TYPE, StreamType*>();
		space.streams->insert(pair<FILE_TYPE, StreamType*>(type, output));
		spaces->insert(pair<std::string, SpacesType>(ns, space));
	}

	return output;
}

bool DBController::close(char* db, char* ns) {
	map<std::string, map<std::string, SpacesType>* >::iterator itDb = _spaces.find(std::string(db));
	if (itDb != _spaces.end()) {
		map<std::string, SpacesType>* spaces = itDb->second;
		map<std::string, SpacesType>::iterator it = spaces->find(std::string(ns));
		if (it != spaces->end()) {
			SpacesType space = it->second;

			map<FILE_TYPE, StreamType*>* streams = space.streams;
			for (map<FILE_TYPE, StreamType*>::iterator istreams = streams->begin(); istreams != streams->end(); istreams++) {
				StreamType* stream = istreams->second;
				stream->close();
				delete stream;
				stream = 0;
			}
			spaces->erase(it);
		}
	}
	return true;
}

void DBController::updateIndex(char* db, char* ns, BSONObj* bson, long filePos) {
	BSONObj indexBSON;
	indexBSON.add("_id", bson->getString("_id"));
	IndexAlgorithm* impl = IndexFactory::indexFactory.index(db, ns, indexBSON);
	Index* index = impl->find(indexBSON);

	index->posData = filePos;

	StreamType* out = open(db, ns, INDEX_FTYPE);
	long currentPos = out->currentPos();
	out->seek(index->indexPos);
	BSONObj* key = index->key;
	writeBSON(out, key);
	out->writeLong(index->indexPos);
	out->writeLong(index->posData);
	out->seek(currentPos);
}

void DBController::insertIndex(char* db, char* ns, BSONObj* bson, long filePos) {
	BSONObj indexBSON;
	std::string id = bson->getString("_id");
	indexBSON.add("_id", id);
	IndexAlgorithm* impl = IndexFactory::indexFactory.index(db, ns, indexBSON);

	StreamType* out = open(std::string(db), std::string(ns), INDEX_FTYPE);

	impl->add(indexBSON, filePos, out->currentPos());

	writeBSON(out, &indexBSON);
	out->writeLong(out->currentPos());
	out->writeLong(filePos);
}

std::vector<BSONObj*>* DBController::findFullScan(char* db, char* ns, const BSONObj& filter) {
	if (_logger->isDebug()) _logger->debug(2, "DBController::findFullScan db: %s, ns: %s, bsonFilter: %s", db, ns, filter.toChar());
	std::string filedir = _dataDir + db;
	filedir = filedir + FILESEPARATOR;

	std::stringstream ss;
	ss << filedir << ns << ".dat";

	std::string filename = ss.str();

	FileInputStream* fis = new FileInputStream(filename.c_str(), "rb");
	std::vector<BSONObj*>* result = new std::vector<BSONObj*>();

	BSONInputStream* bis = new BSONInputStream(fis);
	std::map<t_keytype, BSONContent* >::const_iterator testValIter = filter.begin();
	if (testValIter != filter.end()) {
		BSONContent* testVal = testValIter->second;
		t_keytype keyname = testValIter->first;

		// the first filter will be done over the file
		while (!fis->eof()) {
			BSONObj* readed = bis->readBSON();
			if (readed->has(keyname)) {
				BSONContent* content = readed->getContent(keyname);
				if (*content == *testVal) {
					if (_logger->isDebug()) _logger->debug(2, "found a match with key: %s, obj: %s", keyname.c_str(), readed->toChar());
					result->push_back(readed);
				}
			}
		}

		// now filter the results with the other keys
		testValIter++;
		for ( ;testValIter != filter.end(); testValIter++) {
			std::vector<BSONObj*>* rsTmp = new std::vector<BSONObj*>();
			testVal = testValIter->second;
			keyname = testValIter->first;
			for (std::vector<BSONObj*>::iterator i = result->begin(); i != result->end(); i++) {
				BSONObj* obj = *i;
				if (obj->has(keyname)) {
					BSONContent* content = obj->getContent(keyname);
					if (*content == *testVal) {
						if (_logger->isDebug()) _logger->debug(2, "found a match with key: %s, obj: %s", keyname.c_str(), obj->toChar());
						rsTmp->push_back(obj);
					}
				}
			}
			result = rsTmp;
		}
	} else { // All the records will be included, the filter is empty
		if (_logger->isDebug()) _logger->debug(2, "the filter is empty, all the records will be included from namespace: %s", ns);
		while (!fis->eof()) {
			BSONObj* readed = bis->readBSON();
			result->push_back(readed);
		}

	}

	return result;
}

std::vector<BSONObj*>* DBController::find(char* db, char* ns, const BSONObj& filter) {
	if (_logger->isDebug()) _logger->debug(2, "DBController::find db: %s, ns: %s, bsonFilter: %s", db, ns, filter.toChar());

	std::vector<BSONObj*>* result = new std::vector<BSONObj*>();
	if (filter.has("_id")) {
		std::string id = filter.getString("_id");

		BSONObj indexBSON;
		indexBSON.add("_id", id);
		IndexAlgorithm* impl = IndexFactory::indexFactory.index(db, ns, indexBSON);
		Index* index = impl->find(indexBSON);

		if (index != NULL) {
			StreamType* out = open(db, ns, DATA_FTYPE);
			out->flush();
			//    out->close();

			std::string filedir = _dataDir + db;
			filedir = filedir + FILESEPARATOR;

			std::stringstream ss;
			ss << filedir << ns << ".dat";

			std::string file = ss.str();

			StreamType* input = new StreamType(file, "rb");
			input->seek(index->posData);

			BSONObj* obj = readBSON(input);
			if (_logger->isDebug()) _logger->debug(2, "found a match using _id: %s", obj->toChar());
			result->push_back(obj);
			input->close();
		}
	} else {
		result = findFullScan(db, ns, filter);
	}

	return result;
}

BSONObj* DBController::findFirst(char* db, char* ns, BSONObj* filter) {
	if (_logger->isDebug()) _logger->debug(2, "DBController::findFirst db: %s, ns: %s, bsonFilter: %s", db, ns, filter->toChar());
	std::string id = filter->getString("_id");
	if (CacheManager::objectCache()->containsKey(id)) {
		return (*CacheManager::objectCache())[id];
	}
	std::auto_ptr<std::vector<BSONObj*> > temp(find(db, ns, *filter));
	if (temp->size() == 1) {
		BSONObj* element = *temp->begin();
		CacheManager::objectCache()->add(id, new BSONObj(*element));
		return element;
	} else {
		return NULL;
	}
}

std::vector<BSONObj*>* DBController::find(char* db, char* ns, const char* filter) {
	if (_logger->isDebug()) _logger->debug(2, "DBController::find db: %s, ns: %s, filter: %s", db, ns, filter);

	std::vector<BSONObj*>* result;

	result = findFullScan(db, ns, filter);

	return result;
}

BSONObj* DBController::findFirst(char* db, char* ns, const char* filter) {
	if (_logger->isDebug()) _logger->debug(2, "DBController::findFirst db: %s, ns: %s, filter: %s", db, ns, filter);
	std::string filedir = _dataDir + db;
	filedir = filedir + FILESEPARATOR;

	std::stringstream ss;
	ss << filedir << ns << ".dat";

	std::string filename = ss.str();

	FileInputStream* fis = new FileInputStream(filename.c_str(), "rb");
	std::vector<BSONObj*> result;

	BSONInputStream* bis = new BSONInputStream(fis);

	FilterParser* parser = FilterParser::parse(std::string(filter));

	BSONObj* bsonResult = NULL;
	while (!fis->eof()) {
		BSONObj* obj = bis->readBSON();

		ExpressionResult* result = parser->eval(*obj);
		if (result->type() == ExpressionResult::RT_BOOLEAN) {
			bool* bres = (bool*)result->value();
			if (*bres) {
				bsonResult = obj;
				break;
			}
		}
		delete result;
		delete obj;
		if (bsonResult) {
			break;
		}
	}

	delete parser;
	return bsonResult;
}

std::vector<BSONObj*>* DBController::findFullScan(char* db, char* ns, const char* filter) {
	if (_logger->isDebug()) _logger->debug(2, "DBController::findFullScan db: %s, ns: %s, filter: %s", db, ns, filter);
	std::string filedir = _dataDir + db;
	filedir = filedir + FILESEPARATOR;

	std::stringstream ss;
	ss << filedir << ns << ".dat";

	std::string filename = ss.str();

	FileInputStream* fis = new FileInputStream(filename.c_str(), "rb");
	std::vector<BSONObj*>* result = new std::vector<BSONObj*>();

	BSONInputStream* bis = new BSONInputStream(fis);

	FilterParser* parser = FilterParser::parse(std::string(filter));

	while (!fis->eof()) {
		BSONObj* obj = bis->readBSON();

		bool match = false;
		ExpressionResult* expresult = parser->eval(*obj);
		if (expresult->type() == ExpressionResult::RT_BOOLEAN) {
			bool* bres = (bool*)expresult->value();
			match = *bres;
		}
		if (match) {
			result->push_back(obj);
		} else {
			delete obj;
		}
		delete expresult;
	}

	delete parser;
	delete bis;
	delete fis;

	return result;
}

bool DBController::dropNamespace(char* db, char* ns) {
	StreamType* stream = NULL;
	bool result = false;
	map<std::string, map<std::string, SpacesType>* >::iterator itspaces = _spaces.find(std::string(db));
	if (itspaces == _spaces.end()) {
		return false;
	}
	map<std::string, SpacesType>* spaces = itspaces->second;

	vector<std::string> keysToRemove;

	for (map<std::string, SpacesType>::iterator it = spaces->begin(); it != spaces->end(); it++) {
		std::string key = it->first;

		if (key.compare(ns) == 0) {
			SpacesType space = it->second;

			std::string filedir = _dataDir + std::string(db) + FILESEPARATOR;

			for (map<FILE_TYPE, StreamType*>::iterator istream = space.streams->begin(); istream != space.streams->end(); istream++) {
				FILE_TYPE type = istream->first;
				std::string file = fileName(std::string(ns), type);

				// drops the file
				if (remove((filedir + file).c_str()) != 0) {
					result = false;
					break;
				}
			}
			keysToRemove.push_back(key);
			result = true;
		}
	}
	// remove the elementsss
	for (std::vector<std::string>::iterator it = keysToRemove.begin(); it != keysToRemove.end(); it++) {
		spaces->erase(*it);
	} 
	return result;
}

std::vector<std::string>* DBController::dbs() const {
	std::vector<std::string>* result = new std::vector<std::string>();;

	for (map<std::string, map<std::string, SpacesType>* >::const_iterator it = _spaces.begin(); it != _spaces.end(); it++) {
		std::string db = it->first;
		result->push_back(db);
	}
	return result;
}

std::vector<std::string>* DBController::namespaces(const char* db) const {
	std::vector<std::string>* result = new std::vector<std::string>();;

	map<std::string, map<std::string, SpacesType>* >::const_iterator itspaces = _spaces.find(std::string(db));
	if (itspaces != _spaces.end()) {
		map<std::string, SpacesType>* spaces = itspaces->second;
		for (map<std::string, SpacesType>::iterator it = spaces->begin(); it != spaces->end(); it++) {
			std::string key = it->first;
			std::string ns = key.substr(0, key.find_last_of("."));
			result->push_back(ns);
		}

	}
	return result;
}
