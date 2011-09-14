#include "cachemanager.h"

CacheManager::CacheManager()
{
    _structures = new StructureCache();
}

CacheManager::~CacheManager()
{
    delete _structures;
}


StructureCache* CacheManager::structuresCache() {
    return _structures;
}
