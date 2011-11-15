#ifndef CACHEMANAGER_H
#define CACHEMANAGER_H


#include <map>
#include "cache.h"
#include "structure.h"

using namespace std;

typedef Cache<long, Structure*> StructureCache;
typedef Cache<std::string, BSONObj*> ObjectCache;

class CacheManager
{
    public:
        CacheManager();
        virtual ~CacheManager();

        static StructureCache* structuresCache();
        static ObjectCache* objectCache();
    protected:
    private:
        static StructureCache* structures;
        static ObjectCache* objects;
};

#endif // CACHEMANAGER_H
