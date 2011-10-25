#ifndef INDEXFACTORY_H
#define INDEXFACTORY_H

#include <map>
#include <string>

class IndexAlgorithm;

using namespace std;

class BSONObj;

class IndexFactory
{
    public:
        virtual ~IndexFactory();

        static IndexFactory indexFactory;
        IndexAlgorithm* index(const char* ns, BSONObj key);
    protected:
    private:
        IndexFactory();

    private:

        map<std::string, IndexAlgorithm*> _indexes;
};

#endif // INDEXFACTORY_H
