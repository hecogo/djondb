#ifndef INDEXFACTORY_H
#define INDEXFACTORY_H

#include <map>
#include <string>
#include <set>

class IndexAlgorithm;

using namespace std;

class BSONObj;

class IndexFactory
{
    public:
        virtual ~IndexFactory();

        static IndexFactory indexFactory;
        IndexAlgorithm* index(const char* db, const char* ns, const std::set<std::string>& keys);
        IndexAlgorithm* index(const char* db, const char* ns, const std::string& key);
		  bool containsIndex(const char* db, const char* ns, const std::string& key);
		  bool containsIndex(const char* db, const char* ns, const std::set<std::string>& keys);
    protected:
    private:
        IndexFactory();

    private:

        map<std::string, map<std::string, IndexAlgorithm*>* > _indexes;
};

#endif // INDEXFACTORY_H
