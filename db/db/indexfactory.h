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

		  IndexAlgorithm* findIndex(std::vector<IndexAlgorithm*> algorithms, const std::set<std::string>& keys);

    private:

        map<std::string, map<std::string, std::vector<IndexAlgorithm*> >* > _indexes;
};

#endif // INDEXFACTORY_H
