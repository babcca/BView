#ifndef BIMAGEMANAGER_H
#define BIMAGEMANAGER_H

#include "bsingletoncache.h"
#include "bcache.h"
#include "bimage.h"
#include "fileloaderfactory.h"

class BImageManager
{
public:
    typedef BSingletonCache<BCache<Image *, cache_traits> > imageCache;
    typedef BCache<Image *, cache_traits>::ID IMAGE_ID;
    typedef std::vector<IMAGE_ID> imagesStorage;

    BImageManager();
    void SetFileFactory(FileFactory<ImageFileLoader *> fileFactory);
    void LoadDirectory(const std::wstring & dirName);
    IMAGE_ID LoadImage(QFileInfo & fileInfo);
    struct BImageManagerIterator {
        void operator= (const BImageManagerIterator & it) {
            item = it.item;
        }
        void operator++ () {
            if (++item == imageManager.imagesId.end()) {
                item = imageManager.imagesId.begin();
            }
        }
        /** -- */
        /** @deprecated */
        bool operator== (const BImageManagerIterator & it) const {
            return item == it.item;
        }
        /** @deprecated */
        bool operator!= (const BImageManagerIterator & it) const {
            return !(item == it.item);
        }
        Image * operator-> () {
            return (imageCache::Instance()->GetRecord(*item));
        }

        Image * operator& () {
            return imageCache::Instance()->GetRecord(*item);
        }

        /** @deprecated */
        Image & operator* () {
            return *(imageCache::Instance()->GetRecord(*item));
        }

        void SetItem (imagesStorage::iterator & newItem) {
            item = newItem;
            initialized = true;
        }
        IMAGE_ID GetActualId() {
            return initialized ? *item : -1;
        }
        bool initialized;
    private:
        imagesStorage::iterator item;
        unsigned int revision;
        friend class BImageManager;
        BImageManagerIterator(BImageManager & imageManager_) :
            imageManager(imageManager_),
            initialized(false)
        {
            revision = imageManager.revision;
        }
        BImageManager & imageManager;
    } ActualImage;

private:
    const std::string GetSuffix(const QFileInfo & fileInfo) const;
    FileFactory<ImageFileLoader *> fileFactory;
    imagesStorage imagesId;
    unsigned int revision;
};

#endif // BIMAGEMANAGER_H
