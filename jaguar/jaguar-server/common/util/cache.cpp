/*
 * File:   cache.cpp
 * Author: cross
 *
 * Created on November 8, 2008, 2:37 PM
 */

#include "../util.h"
#include <pthread.h>
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

namespace cache {

    map<string, CacheGroup*> runtimeCache;
    Cache* globalCache;

    CacheItem::CacheItem() {
    }

    CacheItem::~CacheItem() {
        cout << "~CacheItem()" << endl;
        delete(value);
    }

    CacheItem::CacheItem(string newkey, void* newvalue) {
        key = newkey;
        value = newvalue;
    }

    void CacheItem::updateLastTimeUsed() {
        lastTimeUsed = time(NULL);
    }

    long CacheItem::getLastTimeUsed() {
        return lastTimeUsed;
    }

    string CacheItem::getKey() {
        return key;
    }

    void CacheItem::setKey(string newkey) {
        key = newkey;
    }

    void* CacheItem::getValue() {
        return value;
    }

    void CacheItem::setValue(void* newvalue) {
        value = newvalue;
    }

    CacheGroup::CacheGroup() {
    }

    CacheGroup::~CacheGroup() {
        cout << "~CacheGroup()" << endl;
        for (map<string, CacheItem*>::iterator iter = items.begin(); iter != items.end(); iter++) {
            CacheItem* item = iter->second;
            delete(item);
            string key = iter->first;
            key.clear();
            cout << "Borrando CacheItem" << endl;
        }
        items.clear();
    }

    void CacheGroup::add(string key, void* value) {
        CacheItem* item = new CacheItem(key, value);
        items.insert(pair<string, CacheItem* > (key, item));
    }

    void* CacheGroup::get(string key) {
        map<string, CacheItem*>::iterator it = items.find(key);
        if (it == items.end()) {
            return NULL;
        } else {
            CacheItem* item = it->second;
            item->updateLastTimeUsed();
            return item->getValue();
        }
    }

    void CacheGroup::remove(string key) {
        items.erase(key);
    }

    int CacheGroup::size() {
        return items.size();
    }

    void CacheGroup::clear() {
        cout << "CacheGroup::clear()" << endl;
        for (map<string, CacheItem*>::iterator it = items.begin(); it != items.end(); it++) {
            CacheItem* item = it->second;
            delete(item);
        }
    }

    Cache::~Cache() {
        cout << "~Cache()" << endl;
        for (map<string, CacheGroup*>::iterator iter = groups.begin(); iter != groups.end(); iter++) {
            CacheGroup* group = iter->second;
            delete(group);
        }
        groups.clear();
    }
    
    CacheGroup* Cache::get(string key) {
        map<string, CacheGroup*>:: iterator it = groups.find(key);
        CacheGroup* group;
        if (it == groups.end()) {
            group = new CacheGroup();
            groups.insert(pair<string, CacheGroup* > (key, group));
        } else {
            group = it->second;
        }
        return group;
    }

    void Cache::clean() {
        cout << "Cache::clean()" << endl;
        for (map<string, CacheGroup*>::iterator it = groups.begin(); it != groups.end(); it++) {
            CacheGroup* cacheGroup = it->second;
            delete(cacheGroup);
        }
        groups.clear();
    }
    
    CacheGroup* getGlobalCache(string group) {
        if (!globalCache) {
            globalCache = new Cache();
        }
        CacheGroup* cachegroup = globalCache->get(group);
        return cachegroup;
    }

    void cleanGlobalCache() {
        delete(globalCache);
    }
    
    CacheGroup* getRuntimeCache() {
        return NULL;
/*
        string hostAddress = "localhost";
        long threadId = pthread_self();
        string key = hostAddress + "@" + toString(threadId);

        CacheGroup* cache = runtimeCache[key];
        if (!cache) {
            cache = new CacheGroup();
            runtimeCache.insert(pair<string, CacheGroup*>(key, cache));
        }
        return cache;
 */
    }
}
