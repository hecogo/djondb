#ifndef INDEX_H_INCLUDED
#define INDEX_H_INCLUDED

class BSONObj;

struct Index {
    BSONObj* key;
    long posData;
    long indexPos;
};

class IndexAlgorithm {
    public:
    virtual Index* add(BSONObj* elem, long filePos) = 0;
    virtual Index* find(BSONObj* elem) = 0;
    virtual void remove(BSONObj* elem) = 0;
};

#endif // INDEX_H_INCLUDED
