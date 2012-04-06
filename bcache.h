#ifndef BCACHE_H
#define BCACHE_H
#include <map>
class cache_traits {
};


template<typename ItemType, typename CacheTraits>
class BCache {
public:
    typedef unsigned int ID;
    typedef std::map<ID, ItemType> CACHE_STORAGE;
    CACHE_STORAGE cacheItems;

    BCache() : id(0) {}

    ID InsertIntoCache(ItemType item) {
        cacheItems[id] = item;
        return id++;
    }

    ItemType GetRecord(ID id) {
        ItemType cacheItem = cacheItems[id];
        if (!cacheItem->IsCached()) {
            cacheItem->LoadIntoCache();
        }
        return cacheItem;
    }

    void ClearCache() {
        CACHE_STORAGE::iterator i = cacheItems.begin();
        while (i != cacheItems.end()) {
            if ((*i)->IsCached()) {
                (*i)->DeleteFromCache();
            }
            delete *i;
        }
    }

    void DestroyRecord(ID id) {
        auto toDelete = cacheItems.find(id);
        if (toDelete != cacheItems.end()) {
            if (toDelete->second->IsCached()) {
                toDelete->second->DeleteFromCache();
            }
            cacheItems.erase(toDelete);
        } else {
            std::cerr << "ID: " << id << " missed" << std::endl;
        }
    }

private:
    ID id;
};
#endif // BCACHE_H
