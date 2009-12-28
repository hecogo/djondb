#ifndef CACHE_H_INCLUDED
#define CACHE_H_INCLUDED

#include <vector>
#include <map>
#include <string>
#include <ctime>

using namespace std;

namespace cache {

    class CacheItem {
    private:
        long lastTimeUsed;
        string key;
        void* value;

    public:
        void updateLastTimeUsed();
        long getLastTimeUsed();
        CacheItem();
        CacheItem(string key, void* value);
        virtual ~CacheItem();
        string getKey();
        void setKey(string key);
        void* getValue();
        void setValue(void* value);
    };

    class CacheGroup {
    private:
        map<string, CacheItem*> items;

    public:
        CacheGroup();
        virtual ~CacheGroup();

        void add(string key, void* value);

        void* get(string key);

        void remove(string key);

        int size();

        void clear();
    };

    class Cache {
    private:
        map<string, CacheGroup*> groups;

    public:
        virtual ~Cache();

        CacheGroup* get(string key);

        void clean();
    };

    CacheGroup* getGlobalCache(string group);

    CacheGroup* getRuntimeCache();

    void cleanGlobalCache();
}

#endif
