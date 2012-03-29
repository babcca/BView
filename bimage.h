#ifndef BIMAGE_H
#define BIMAGE_H
#include "icacheitem.h"
#include "fileloader.h"

class Image : public ICacheItem {
public:
    Image(FileLoader * file_cache_id_) : file_cache(file_cache_id_) {
        IsCached(false);
    }
    ~Image() {
        delete file_cache;
    }

    virtual void LoadIntoCache() {
        std::cout << "ImageLoadIntoCache" << std::endl;
        //typedef BSingletonCache<BCache<FileLoader *, cache_traits> > fileCache;
        //auto instance = fileCache::Instance();
        //FileLoader * file = instance->GetRecord(file_cace_id);
        file_cache->LoadIntoCache();

    }

    virtual void DeleteFromCache() {
        std::cout << "ImageDelete" << std::endl;
        file_cache->DeleteFromCache();

    }

    virtual void UnloadFromCache() {
        std::cout << "ImageUnload" << std::endl;
        file_cache->UnloadFromCache();
    }

    FileLoader * file_cache;
};


#endif // BIMAGE_H
