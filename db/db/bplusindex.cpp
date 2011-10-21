#include "bplusindex.h"

#include "bson.h"

#include <string.h>
#include <boost/crc.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>

BPlusIndex::BPlusIndex()
{

    _head = new Bucket();
    initializeBucket(_head);
}

//void cascadeDelete(IndexPointer* element) {
/*
if (element->left != NULL) {
    cascadeDelete(element->left);
}
if (element->right != NULL) {
    cascadeDelete(element->right);
}
if (element->elem) {
    Index* index = element->elem;
    delete index->key;
    delete index;
}
if (element->value != NULL) {
    free(element->value);
}
delete element;
*/
//}

BPlusIndex::~BPlusIndex()
{
    if (_head)
    {
//        cascadeDelete(_head);
    }
}

Index* BPlusIndex::add(BSONObj* elem, long filePos)
{
    Index* index = new Index();
    index->key = elem;
    index->posData = filePos;

    bool inserted = insertElement(index);
    if (!inserted)
    {
        delete elem;
    }
    return index;
}

Index* BPlusIndex::find(BSONObj* elem)
{
//    char* key = elem->toChar();
//    boost::crc_32_type crc32;
//    crc32.process_bytes(key, strlen(key));
//    long value = crc32.checksum();

    BucketElement* element = findBucketElement(_head, elem);
    if (element->index == NULL)
    {
        Index* index = new Index();
        index->key = elem;
        element->index = index;
    }
    return element->index;
}

void BPlusIndex::remove(BSONObj* elem)
{
}

void BPlusIndex::initializeBucketElement(BucketElement* const elem)
{
    elem->index = NULL;
    elem->next = NULL;
    elem->previous = NULL;
}

void BPlusIndex::initializeBucket(Bucket* const bucket)
{
    bucket->minKey = NULL;
    bucket->maxKey = NULL;
    bucket->root = NULL;
    bucket->size = 0;
    bucket->tail = NULL;
}

void BPlusIndex::checkBucket(Bucket* const bucket)
{
    if (bucket->size == BUCKET_MAX_ELEMENTS) {
        // The bucked will be split
        Bucket* leftBucket = new Bucket();
        initializeBucket(leftBucket);
        bucket->left = leftBucket;

        BucketElement* leftElement = bucket->root;
        BucketElement* rightElement = bucket->tail;

        // Move the elements
        bucket->root = bucket->root->next;
        bucket->minKey = bucket->root->key;

        Bucket* rightBucket = new Bucket();
        initializeBucket(rightBucket);
        bucket->right = rightBucket;

        leftElement->next = NULL;
        rightElement->next = NULL;
        bucket->root->next = NULL;

        bucket->tail = bucket->root;
        bucket->maxKey = bucket->tail->key;
        bucket->size -= 2;

        insertBucketElement(leftBucket, leftElement);
        insertBucketElement(rightBucket, rightElement);

    }
}

// This method will insert the element into the currentBucket
void BPlusIndex::insertBucketElement(Bucket* bucket, BucketElement* element)
{
    INDEXPOINTERTYPE key = element->key;
    BucketElement* currentElement = bucket->root;
    if (currentElement == NULL) {
        bucket->root = element;
        bucket->tail = element;
        bucket->size++;
        bucket->minKey = element->key;
        bucket->maxKey = element->key;
        return;
    }
    // Insert in the current bucket
    while (true) {
        INDEXPOINTERTYPE testKey = currentElement->key;
        int comp = strcmp(key, testKey);
        if (comp == 0)
        {
            return;
        }
        else
        {
            // The value is lesser than the current, should be inserted in front
            // if there's enough space
            if (comp < 0)
            {
                if (currentElement == bucket->root)
                {
                    element->next = currentElement;
                    bucket->root = element;
                    bucket->minKey = element->key;
                }
                else
                {
                    currentElement->previous->next = element;
                    currentElement->previous = element;
                }
                bucket->size++;
                break;
            }
            else
            {
                // the value is greater and should be added to the next
                if (currentElement == bucket->tail)
                {
                    currentElement->next = element;
                    element->previous = currentElement;
                    bucket->maxKey = element->key;
                    bucket->tail = element;
                    bucket->size++;
                    break;
                } else {
                    // Moves to the next node
                    currentElement = currentElement->next;
                }
            }
        }
    }
    checkBucket(bucket);
}

int compKey(BucketElement* element, INDEXPOINTERTYPE key) {
    INDEXPOINTERTYPE testKey = element->key;
    return strcmp(testKey, key);
}

/***
This will find the bucket in which the key should be in
*/
BucketElement* BPlusIndex::findBucketElement(Bucket* start, BSONObj* bkey)
{
    Bucket* currentBucket = start;
    INDEXPOINTERTYPE key = bkey->toChar();
    if (currentBucket->size == 0)
    {
        BucketElement* element = new BucketElement();
        initializeBucketElement(element);
        Index* index = new Index();
        index->key = bkey;
        element->index = index;
        element->key = key;
        insertBucketElement(currentBucket, element);
        return element;
    }
    else
    {
        while (true)
        {
            int comp = strcmp(key, currentBucket->minKey);

            // Lucky the min is the one we're looking for
            if (comp == 0)
            {
                return currentBucket->root;
            }
            else if (comp < 0)
            {
                // If the value is less than current left element in bucket and there's leaf then should test on that
                if (currentBucket->left != NULL)
                {
                    currentBucket = currentBucket->left;
                    continue;
                }
            }

            comp = strcmp(key, currentBucket->maxKey);
            if (comp == 0) {
                return currentBucket->tail;
            } else if (comp > 0) {
                if (currentBucket->right != NULL) {
                    currentBucket = currentBucket->right;
                    continue;
                }
            }
            BucketElement* element = new BucketElement();
            initializeBucketElement(element);
            Index* index = new Index();
            index->key = bkey;
            element->index = index;
            element->key = key;
            insertBucketElement(currentBucket, element);
            return element;
        }
    }
}

bool BPlusIndex::insertElement(Index* elem)
{
    BSONObj* obj = elem->key;
    char* key = obj->toChar();
    bool inserted = false;

    findBucketElement(_head, obj);

    return true;
}
