#include <iostream>

#include "cachemanager.h"
#include <assert.h>

using namespace std;

int testCache() {
    StructureCache* cache = new StructureCache();
    Structure* str = new Structure();
    str->add("name");
    str->add("lastName");
    long id = str->crc();
    CacheManager::structuresCache()->add(id, str);

    Structure* str2 = new Structure();
    str2->add("name");
    str2->add("lastName");
    long id2 = str->crc();
    CacheManager::structuresCache()->add(id2, str);

    Structure* s2 = (*CacheManager::structuresCache())[id];
    assert (s2 == str);

    assert (s2 != str2);
}

int main()
{
    testCache();
    return 0;
}
