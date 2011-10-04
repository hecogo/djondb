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
}

boost::shared_ptr<IndexAlgorithm> IndexFactory::index(const char* ns, boost::shared_ptr<BSONObj> key) {
    std::stringstream ss;
    ss << "ns:" << ns << ":";
    for (std::map<t_keytype, boost::shared_ptr<BSONContent> >::const_iterator i = key->begin(); i != key->end(); i++) {
        ss << i->first << ";";
    }
    std::string skey = ss.str();
    map<std::string, boost::shared_ptr<IndexAlgorithm> >::iterator iIndex = _indexes.find(skey);
    boost::shared_ptr<IndexAlgorithm> indexImpl;
    if (iIndex == _indexes.end()) {
        indexImpl = boost::shared_ptr<BPlusIndex>(new BPlusIndex());
        _indexes.insert(pair<std::string, boost::shared_ptr<IndexAlgorithm> >(skey, indexImpl));
    } else {
        indexImpl =iIndex->second;
    }

    return indexImpl;
}
