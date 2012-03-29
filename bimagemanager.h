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

    BImageManager(const FileFactory & fileFactory);
    void SetDirectory(const std::wstring & dirName);
    void LoadImage();
    void GetIterator();
private:
    FileFactory fileFactory;
    BDirectory directory;
};

#endif // BIMAGEMANAGER_H
