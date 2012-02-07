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
#include <sstream>
#include <string>

IndexFactory IndexFactory::indexFactory;

IndexFactory::IndexFactory()
{
    //ctor
}

IndexFactory::~IndexFactory()
{
    for (map<std::string, IndexAlgorithm*>::iterator i = _indexes.begin(); i != _indexes.end(); i++) {
        IndexAlgorithm* alg = i->second;
        delete alg;
    }
}

bool IndexFactory::containsIndex(const char* ns, BSONObj key) {
    std::stringstream ss;
    ss << "ns:" << ns << ":";
    for (std::map<t_keytype, BSONContent* >::const_iterator i = key.begin(); i != key.end(); i++) {
        ss << i->first << ";";
    }
    std::string skey = ss.str();
    map<std::string, IndexAlgorithm*>::iterator iIndex = _indexes.find(skey);
    if (iIndex == _indexes.end()) {
		 return false;
    } else {
		 return true;
	 }
}

IndexAlgorithm* IndexFactory::index(const char* ns, BSONObj key) {
    std::stringstream ss;
    ss << "ns:" << ns << ":";
    for (std::map<t_keytype, BSONContent* >::const_iterator i = key.begin(); i != key.end(); i++) {
        ss << i->first << ";";
    }
    std::string skey = ss.str();
    map<std::string, IndexAlgorithm*>::iterator iIndex = _indexes.find(skey);
    IndexAlgorithm* indexImpl;
    if (iIndex == _indexes.end()) {
        indexImpl = new BPlusIndex();
        _indexes.insert(pair<std::string, IndexAlgorithm*>(skey, indexImpl));
    } else {
        indexImpl =iIndex->second;
    }

    return indexImpl;
}
