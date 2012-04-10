#ifndef BIMAGE_H
#define BIMAGE_H
#include "icacheitem.h"
#include "bimagefileloader.h"
#include "globalstruct.h"

class Image : public ICacheItem {
public:
    Image(ImageFileLoader * file_cache_id_);
    ~Image();
    virtual void LoadIntoCache();
    virtual void DeleteFromCache();

    void SetImageInfo(const ImageInfo & imageInfo) ;
    void AllocateMemmory();

    const int GetWidth() const;
    const int GetHeight() const;
    const int GetBitCount() const;
    const int GetPixelSize() const;
    const int GetPixelFormat() const;
    const RGBA GetPixel(int row, int col);
    Image * Clone();
    DataAllocator ImageData;
    ImageInfo imageInfo;
private:
    ImageFileLoader * fileLoader;

};


#endif // BIMAGE_H
