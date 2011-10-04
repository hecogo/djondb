#ifndef INDEX_H_INCLUDED
#define INDEX_H_INCLUDED

#include <memory>
#include <boost/shared_ptr.hpp>

class BSONObj;

struct Index {
    boost::shared_ptr<BSONObj> key;
    long posData;
    long indexPos;
};

class IndexAlgorithm {
    public:
    virtual boost::shared_ptr<Index> add(boost::shared_ptr<BSONObj> elem, long filePos) = 0;
    virtual boost::shared_ptr<Index> find(boost::shared_ptr<BSONObj> elem) = 0;
    virtual void remove(BSONObj* elem) = 0;
};

#endif // INDEX_H_INCLUDED
