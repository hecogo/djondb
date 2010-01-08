#include "keys.h"

#include <map>
#include <string>

using namespace std;

map<string, int> keys;

int getNextKey(string table) {
    map<string, int>::iterator iter = keys.find(table);
    if (iter == keys.end()) {
        pair < map<string, int>::iterator, bool> res = keys.insert(pair<string, int>(table, 0));
        if (res.second) {
            iter = res.first;
        } else {
            iter = keys.find(table);
        }
    }
    int key = ++iter->second;
    return key;
}

