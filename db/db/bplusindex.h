#ifndef BPLUSINDEX_H
#define BPLUSINDEX_H

#include "index.h"

typedef char* INDEXPOINTERTYPE;

struct IndexPointer {
    Index* elem;
    INDEXPOINTERTYPE value;

    IndexPointer* left;
    IndexPointer* right;
};

class BPlusIndex: public IndexAlgorithm
{
    public:
        BPlusIndex();
        virtual ~BPlusIndex();

        virtual Index* add(BSONObj* elem, long filePos);
        virtual Index* find(BSONObj* elem);
        virtual void remove(BSONObj* elem);
    protected:
    private:
        IndexPointer* _head;

    private:
        void insertElement(Index* elem);
        IndexPointer* findNode(IndexPointer* start, INDEXPOINTERTYPE value);
};

#endif // BPLUSINDEX_H
