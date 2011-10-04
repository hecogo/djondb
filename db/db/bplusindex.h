#ifndef BPLUSINDEX_H
#define BPLUSINDEX_H

#include "index.h"
#include <memory>
#include <boost/shared_ptr.hpp>

typedef char* INDEXPOINTERTYPE;

struct IndexPointer {
    boost::shared_ptr<Index> elem;
    INDEXPOINTERTYPE value;

    boost::shared_ptr<IndexPointer> left;
    boost::shared_ptr<IndexPointer> right;
};

class BPlusIndex: public IndexAlgorithm
{
    public:
        BPlusIndex();
        virtual ~BPlusIndex();

        virtual boost::shared_ptr<Index> add(boost::shared_ptr<BSONObj> elem, long filePos);
        virtual boost::shared_ptr<Index> find(boost::shared_ptr<BSONObj> elem);
        virtual void remove(BSONObj* elem);
    protected:
    private:
        boost::shared_ptr<IndexPointer> _head;

    private:
        void insertElement(boost::shared_ptr<Index> elem);
        boost::shared_ptr<IndexPointer> findNode(boost::shared_ptr<IndexPointer> start, INDEXPOINTERTYPE value);
};

#endif // BPLUSINDEX_H
