/*
 * File:   cache.cpp
 * Author: cross
 *
 * Created on November 8, 2008, 2:37 PM
 */

#include "util.h"
#include <pthread.h>
#include <iostream>

using namespace std;

namespace cache {

    map<string, CacheGroup*> runtimeCache;
    Cache* globalCache;

    CacheItem::CacheItem() {
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

    void CacheGroup::add(string key, void* value) {
        CacheItem* item = new CacheItem(key, value);
        items.insert(pair<string, CacheItem* > (key, item));
    }

    void* CacheGroup::get(string key) {
        CacheItem* item = items.find(key)->second;
        if (!item) {
            return NULL;
        } else {
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

    CacheGroup Cache::get(string key) {
//        map<string,CacheGroup*>::iterator it;
//        for (it = groups.begin(); it != groups.end(); it++) {
//            cout << (*it).first << ":" << (*it).second << endl;
//        }
        CacheGroup* group = groups.find(key)->second;
        if (!group) {
            group = new CacheGroup();
            groups.insert(pair<string, CacheGroup* > (key, group));
        }
        return *group;
    }

    CacheGroup getGlobalCache(string group) {
        if (!globalCache) {
            globalCache = new Cache();
        }
        CacheGroup cachegroup = globalCache->get(group);
        return cachegroup;
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
