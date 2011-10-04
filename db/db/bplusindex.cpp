#include "bplusindex.h"

#include "bson.h"

#include <string.h>
#include <boost/crc.hpp>

BPlusIndex::BPlusIndex()
{
}

BPlusIndex::~BPlusIndex()
{
    //dtor
}

boost::shared_ptr<Index> BPlusIndex::add(boost::shared_ptr<BSONObj> elem, long filePos) {
    boost::shared_ptr<Index> index(new Index());
    index->key = elem;
    index->posData = filePos;

    insertElement(index);
    return index;
}

boost::shared_ptr<Index> BPlusIndex::find(boost::shared_ptr<BSONObj> elem) {
    char* key = elem->toChar();
//    boost::crc_32_type crc32;
//    crc32.process_bytes(key, strlen(key));
//    long value = crc32.checksum();

    boost::shared_ptr<IndexPointer> pointer = findNode(_head, key);
    if (pointer->elem.get() == NULL) {
        boost::shared_ptr<Index> index(new Index());
        index->key = elem;
        pointer->elem = index;
    }
    return pointer->elem;
}

void BPlusIndex::remove(BSONObj* elem) {
}

boost::shared_ptr<IndexPointer> BPlusIndex::findNode(boost::shared_ptr<IndexPointer> start, INDEXPOINTERTYPE value) {
    if (_head.get() == NULL) {
        _head = boost::shared_ptr<IndexPointer>(new IndexPointer);
        _head->value = value;
        return _head;
    } else {
        boost::shared_ptr<IndexPointer> current = start;
        if (strcmp(current->value, value) > 0) {
            if (current->left.get() == NULL) {
                boost::shared_ptr<IndexPointer> pointer(new IndexPointer());
                pointer->value = value;
                current->left = pointer;
                return pointer;
            } else {
                return findNode(current->left, value);
            }
        } else if (strcmp(current->value, value) < 0) {
            if (current->right.get() == NULL) {
                boost::shared_ptr<IndexPointer> pointer(new IndexPointer());
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

void BPlusIndex::insertElement(boost::shared_ptr<Index> elem) {
    boost::shared_ptr<BSONObj> obj = elem->key;
    char* key = obj->toChar();
//    boost::crc_32_type crc32;
//    crc32.process_bytes(key, strlen(key));
//    long value = crc32.checksum();

    boost::shared_ptr<IndexPointer> node;
    if (_head.get() != NULL) {
        _head = boost::shared_ptr<IndexPointer>(new IndexPointer());
        _head->elem = elem;
        _head->value = key;
        node = _head;
    } else {
        boost::shared_ptr<IndexPointer> node = findNode(_head, key);
        node->elem = elem;
    }
}
