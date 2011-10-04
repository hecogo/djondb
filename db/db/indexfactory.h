#ifndef INDEXFACTORY_H
#define INDEXFACTORY_H

#include <map>
#include <string>
#include <boost/shared_ptr.hpp>

class IndexAlgorithm;

using namespace std;

class BSONObj;

class IndexFactory
{
    public:
        virtual ~IndexFactory();

        static IndexFactory* indexFactory;
        boost::shared_ptr<IndexAlgorithm> index(const char* ns, boost::shared_ptr<BSONObj> key);
    protected:
    private:
        IndexFactory();

    private:

        map<std::string, boost::shared_ptr<IndexAlgorithm> > _indexes;
};

#endif // INDEXFACTORY_H
