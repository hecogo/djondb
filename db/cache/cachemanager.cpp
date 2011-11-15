#include "cachemanager.h"

StructureCache* CacheManager::structures = new StructureCache();
ObjectCache* CacheManager::objects = new ObjectCache();

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

ObjectCache* CacheManager::objectCache() {
    return objects;
}
