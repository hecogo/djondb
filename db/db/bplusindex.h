#ifndef BPLUSINDEX_H
#define BPLUSINDEX_H

#include "index.h"
#include <boost/shared_ptr.hpp>

typedef char* INDEXPOINTERTYPE;

const int BUCKET_MAX_ELEMENTS = 9; // Should be even (3, 5, 7)

struct BucketElement {
    Index* index;

    INDEXPOINTERTYPE key;

    BucketElement* previous;
    BucketElement* next;
};

struct Bucket {
    int size;
    INDEXPOINTERTYPE minKey;
    INDEXPOINTERTYPE maxKey;

    BucketElement* root;
    BucketElement* tail;

    Bucket* left;
    Bucket* right;

    Bucket* parentBucket;
};

class BPlusIndex: public IndexAlgorithm
{
    public:
        BPlusIndex();
        virtual ~BPlusIndex();

        virtual void add(const BSONObj& elem, long filePos, long indexPos);
        virtual Index* find(const BSONObj& elem);
        virtual void remove(const BSONObj& elem);
    protected:
    private:
        Bucket* _head;

    private:
        bool insertElement(const Index& elem);
        BucketElement* findBucketElement(Bucket* start, const Index& idx, bool create);
        void initializeBucket(Bucket* const element);
        void initializeBucketElement(BucketElement* const elem);

        void insertBucketElement(Bucket* bucket, BucketElement* element);
        void checkBucket(Bucket* const bucket);
};

#endif // BPLUSINDEX_H
