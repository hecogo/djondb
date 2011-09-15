#include "cachemanager.h"

StructureCache* CacheManager::structures = new StructureCache();

CacheManager::CacheManager()
{
}

CacheManager::~CacheManager()
{
//    delete _structures;
}

StructureCache* CacheManager::structuresCache() {
    return structures;
}


