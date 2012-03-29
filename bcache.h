#ifndef BCACHE_H
#define BCACHE_H
template<typename ItemType, typename CacheTraits>
class BCache {
public:
    typedef unsigned int ID;
    typedef std::vector<ItemType> CACHE_STORAGE;
    CACHE_STORAGE cacheItems;

    BCache() : id(0) {}
    ~BCache() {
        CACHE_STORAGE::iterator i = cacheItems.begin();
        while (i != cacheItems.end()) {
            delete (*i);
            ++i;
        }
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

private:
    ID id;
};
#endif // BCACHE_H
