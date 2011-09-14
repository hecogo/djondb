#include <iostream>

#include "cachemanager.h"

using namespace std;

int testCache() {
    StructureCache* cache = new StructureCache();
    Structure* str = new Structure();
    str->add("name");
    str->add("lastName");
    long id = str->crc();
    cache->add(id, str);

    Structure* str2 = new Structure();
    str2->add("name");
    str2->add("lastName");
    long id2 = str->crc();
    cache->add(id2, str);

    Structure* s2 = (*cache)[id];
    if (s2 == str) {
        cout << "Yuju!" << endl;
    }
    if (s2 == str2) {
        cout << "Yuju 2!" << endl;
    }
}

int main()
{
    testCache();
    return 0;
}
