#ifndef BPLUSINDEX_H
#define BPLUSINDEX_H

#include "index.h"


struct IndexPointer {
    Index* elem;
    long value;

    IndexPointer* left;
    IndexPointer* right;
};

class BPlusIndex: public IndexAlgorithm
{
    public:
        BPlusIndex();
        virtual ~BPlusIndex();

        virtual void add(BSONObj* elem, long filePos);
        virtual Index* find(BSONObj* elem);
        virtual void remove(BSONObj* elem);
    protected:
    private:
        IndexPointer* _head;

    private:
        void insertElement(Index* elem);
        IndexPointer* findNode(IndexPointer* start, long value);
};

#endif // BPLUSINDEX_H
