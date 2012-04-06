#ifndef BCACHE_H
#define BCACHE_H

class cache_traits {
};


template<typename ItemType, typename CacheTraits>
class BCache {
public:
    typedef unsigned int ID;
    typedef std::vector<ItemType> CACHE_STORAGE;
    CACHE_STORAGE cacheItems;

    BCache() : id(0) {}
    ~BCache() {

    }

    ID InsertIntoCache(ItemType item) {
        cacheItems.push_back(item);
        return cacheItems.size() - 1;
    }

    ItemType GetRecord(ID id) {
        ItemType cacheItem = cacheItems[id];
        if (!cacheItem->IsCached()) {
            cacheItem->LoadIntoCache();
        }
        return cacheItem;
    }

    void FreeCache() {
        CACHE_STORAGE::iterator i = cacheItems.begin();
        while (i != cacheItems.end()) {
            delete (*i);
            (*i) = 0;
            ++i;
        }
    }

private:
    ID id;
};
#endif // BCACHE_H
