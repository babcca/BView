#ifndef BSINGLETONCACHE_H
#define BSINGLETONCACHE_H
#include "bdirectory.h"
#include <vector>
#include <assert.h>

template<typename CacheType>
class BSingletonCache
{
public:
    static CacheType * Instance() {
        if (cacheInstance == 0) {
            cacheInstance = new CacheType();
        }
        assert(cacheInstance != 0);
        return cacheInstance;
    }
protected:
    BSingletonCache();
    virtual ~BSingletonCache();
private:
    BSingletonCache(const BSingletonCache &);
    BSingletonCache & operator = (const BSingletonCache &);
    static CacheType * cacheInstance;

};

template<typename CacheType> CacheType * BSingletonCache<CacheType>::cacheInstance = 0;

#endif // BSINGLETONCACHE_H
