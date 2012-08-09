#ifndef INDEX_H_INCLUDED
#define INDEX_H_INCLUDED

#include <list>

class BSONObj;
class FilterParser;

struct Index {
    BSONObj* key;
    long posData;
    long indexPos;
};

class IndexAlgorithm {
    public:
    virtual ~IndexAlgorithm() {};
    virtual void add(const BSONObj& elem, long filePos, long indexPos) = 0;
    virtual Index* find(const BSONObj& elem) = 0;
    virtual void remove(const BSONObj& elem) = 0;
	 virtual std::list<Index*> find(FilterParser* parser) = 0;
};

#endif // INDEX_H_INCLUDED
