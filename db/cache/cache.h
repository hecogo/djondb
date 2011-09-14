#ifndef CACHE_H
#define CACHE_H

#include <map>

using namespace std;

template <class K, class V>
class Cache
{
    public:
        Cache();
        virtual ~Cache();
        Cache(const Cache& other);

        void add(const K& key, const V& val);
        void remove(const K& key);

        V operator[](const K& key);

    protected:
    private:
        map<K, V> _elements;
};

template <class K, class V>
Cache<K, V>::Cache()
{
    //ctor
}

template <class K, class V>
Cache<K, V>::~Cache()
{
    //dtor
}

template <class K, class V>
Cache<K, V>::Cache(const Cache& other)
{
    //copy ctor
}

template <class K, class V>
void Cache<K, V>::remove(const K& key)
{
    // look at http://www.parashift.com/c++-faq-lite/templates.html#faq-35.18 (Whoa new for me)
    typename map<K,V>::iterator i = _elements.find(key);
    if (i != _elements.end()) {
        _elements.erase(i);
    }
}

template <class K, class V>
void Cache<K, V>::add(const K& key, const V& val) {
    _elements.insert(pair<K, V> (key, val));
}

template <class K, class V>
V Cache<K, V>::operator [](const K& key) {
    typename map<K,V>::iterator i = _elements.find(key);
    if (i != _elements.end()) {
        return i->second;
    }
}


#endif // CACHE_H
