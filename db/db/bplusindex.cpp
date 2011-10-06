#include "bplusindex.h"

#include "bson.h"

#include <string.h>
#include <boost/crc.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>

BPlusIndex::BPlusIndex()
{
    _head = NULL;
}

void cascadeDelete(IndexPointer* element) {
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
}

BPlusIndex::~BPlusIndex()
{
    if (_head) {
        cascadeDelete(_head);
    }
}

Index* BPlusIndex::add(BSONObj* elem, long filePos) {
    Index* index = new Index();
    index->key = elem;
    index->posData = filePos;

    bool inserted = insertElement(index);
    if (!inserted) {
        delete elem;
    }
    return index;
}

Index* BPlusIndex::find(BSONObj* elem) {
    char* key = elem->toChar();
//    boost::crc_32_type crc32;
//    crc32.process_bytes(key, strlen(key));
//    long value = crc32.checksum();

    IndexPointer* pointer = findNode(_head, key);
    if (pointer->elem == NULL) {
        Index* index = new Index();
        index->key = elem;
        pointer->elem = index;
    }
    return pointer->elem;
}

void BPlusIndex::remove(BSONObj* elem) {
}

IndexPointer* BPlusIndex::findNode(IndexPointer* start, INDEXPOINTERTYPE value) {
    if (_head == NULL) {
        _head = new IndexPointer;
        _head->left = NULL;
        _head->right = NULL;
        _head->value = value;
        _head->elem = NULL;
        return _head;
    } else {
        IndexPointer* current = start;
        if (strcmp(current->value, value) > 0) {
            if (current->left == NULL) {
                IndexPointer* pointer = new IndexPointer();
                pointer->right = NULL;
                pointer->elem = NULL;
                pointer->value = value;
                current->left = pointer;
                return pointer;
            } else {
                return findNode(current->left, value);
            }
        } else if (strcmp(current->value, value) < 0) {
            if (current->right == NULL) {
                IndexPointer* pointer = new IndexPointer();
                pointer->left = NULL;
                pointer->elem = NULL;
                pointer->value = value;
                current->right = pointer;
                return pointer;
            } else {
                return findNode(current->right, value);
            }
        } else {
            return current;
        }
    }
}

bool BPlusIndex::insertElement(Index* elem) {
    BSONObj* obj = elem->key;
    char* key = obj->toChar();
    bool inserted = false;
//    boost::crc_32_type crc32;
//    crc32.process_bytes(key, strlen(key));
//    long value = crc32.checksum();

    IndexPointer* node = NULL;
    if (!_head) {
        _head = new IndexPointer();
        _head->elem = elem;
        _head->left = 0;
        _head->right = 0;
        _head->value = key;
        node = _head;
        inserted = true;
    } else {
        IndexPointer* node = findNode(_head, key);
        if (!node->elem) {
            node->elem = elem;
            inserted = true;
        }
    }
    return inserted;
}
