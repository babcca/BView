#include "bimage.h"

Image::Image(ImageFileLoader * file_cache_id_)
    : fileLoader(file_cache_id_)
{
    IsCached(false);
}

Image::~Image() {
//    DeleteFromCache();
//    delete fileLoader;
}

void Image::LoadIntoCache() {
    if (!IsCached()) {
        std::cout << "ImageLoadIntoCache" << std::endl;
        fileLoader->LoadIntoCache();
        fileLoader->Decode(this);
        IsCached(true);
    }
}

void Image::DeleteFromCache() {
    std::cout << "ImageDelete" << std::endl;
    fileLoader->DeleteFromCache();

}

void Image::UnloadFromCache() {
    std::cout << "ImageUnload" << std::endl;
    fileLoader->UnloadFromCache();
}

void Image::SetImageInfo(const ImageInfo &imageInfo) {
    this->imageInfo = imageInfo;
}
const int Image::GetWidth() const {
    return imageInfo.width;
}
const int Image::GetHeight() const {
    return imageInfo.height;
}
const int Image::GetBitCount() const {
    return imageInfo.bitCount;
}
const int Image::GetPixelSize() const {
    return imageInfo.pixelSize;
}
const int Image::GetPixelFormat() const {
    return imageInfo.pixelFormat;
}
void Image::AllocateMemmory() {
    ImageData.AllocateDataMemory(imageInfo.imageSize);
}
