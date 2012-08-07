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

#include "indexfactory.h"

#include "bson.h"
#include "bplusindex.h"
#include <stdio.h>
#include <sstream>
#include <string>

IndexFactory IndexFactory::indexFactory;

std::string indexkey(const char* ns, const std::set<std::string>& keys) {
	char buffer[3000];
	memset(buffer, 0, 3000);
	sprintf(buffer, "ns:%s", ns);
	int pos = strlen(ns);
	for (std::set<std::string>::iterator it = keys.begin(); it != keys.end(); it++) {
		std::string s = *it;
		sprintf(buffer + pos, "%s:", s.c_str());
		pos += s.length();
	}

	std::string skey = std::string(buffer);
	return skey;
}

IndexFactory::IndexFactory()
{
    //ctor
}

IndexFactory::~IndexFactory()
{
	for (map<std::string, map<std::string, IndexAlgorithm*>* >::iterator iDb = _indexes.begin(); iDb != _indexes.end(); iDb++) {
		map<std::string, IndexAlgorithm*>* indexes = iDb->second;
		for (map<std::string, IndexAlgorithm*>::iterator i = indexes->begin(); i != indexes->end(); i++) {
			IndexAlgorithm* alg = i->second;
			delete alg;
		}
		delete indexes;
	}
}

bool IndexFactory::containsIndex(const char* db, const char* ns, const std::string& key) {
	std::set<std::string> keys;
	keys.insert(key);
	return containsIndex(db, ns, keys);
}

bool IndexFactory::containsIndex(const char* db, const char* ns, const std::set<std::string>& keys) {
	map<std::string, map<std::string, IndexAlgorithm*>* >::iterator itIndexes = _indexes.find(std::string(db));
	if (itIndexes != _indexes.end()) {	
		std::map<std::string, IndexAlgorithm*>* indexes = itIndexes->second;
		std::string skey = indexkey(ns, keys); 

		map<std::string, IndexAlgorithm*>::iterator iIndex = indexes->find(skey);
		if (iIndex == indexes->end()) {
			return false;
		} else {
			return true;
		}
	} else {
		return false;
	}
}

IndexAlgorithm* IndexFactory::index(const char* db, const char* ns, const std::string& key) {
	std::set<std::string> skeys;
	skeys.insert(key);
	return index(db, ns, skeys);
}

IndexAlgorithm* IndexFactory::index(const char* db, const char* ns, const std::set<std::string>& keys) {
	map<std::string, map<std::string, IndexAlgorithm*>* >::iterator itIndexes = _indexes.find(db);
	std::map<std::string, IndexAlgorithm*>* indexes;
	if (itIndexes == _indexes.end()) {
		indexes = new std::map<std::string, IndexAlgorithm*>();
		_indexes.insert(pair<std::string, map<std::string, IndexAlgorithm*>* >(std::string(db), indexes));
	} else {
		indexes = itIndexes->second;
	}

	std::string skey = indexkey(ns, keys);

	map<std::string, IndexAlgorithm*>::iterator iIndex = indexes->find(skey);
	IndexAlgorithm* indexImpl;
	if (iIndex == indexes->end()) {
		indexImpl = new BPlusIndex();
		indexes->insert(pair<std::string, IndexAlgorithm*>(skey, indexImpl));
	} else {
		indexImpl = iIndex->second;
	}

	return indexImpl;
}
