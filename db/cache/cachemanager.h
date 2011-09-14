#ifndef CACHEMANAGER_H
#define CACHEMANAGER_H


#include <map>
#include "cache.h"
#include "structure.h"

using namespace std;

typedef Cache<long, Structure*> StructureCache;
class CacheManager
{
    public:
        CacheManager();
        virtual ~CacheManager();

        StructureCache* structuresCache();
    protected:
    private:
        StructureCache* _structures;

};

#endif // CACHEMANAGER_H
