#include "indexfactory.h"

#include "bson.h"
#include "bplusindex.h"
#include <sstream>
#include <string>

IndexFactory* IndexFactory::indexFactory = new IndexFactory();

IndexFactory::IndexFactory()
{
    //ctor
}

IndexFactory::~IndexFactory()
{
    //dtor
}

IndexAlgorithm* IndexFactory::index(char* ns, BSONObj* key) {
    std::stringstream ss;
    ss << "ns:" << ns << ":";
    for (std::map<t_keytype, BSONContent* >::const_iterator i = key->begin(); i != key->end(); i++) {
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
