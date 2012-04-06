#include "bimage.h"

Image::Image(ImageFileLoader * file_cache_id_)
    : fileLoader(file_cache_id_)
{
    IsCached(false);
}

Image::~Image() {
    DeleteFromCache();
    if (fileLoader != 0) {
        delete fileLoader;
        fileLoader = 0;
    }
}

const RGBA Image::GetPixel(int row, int col) {
    int dataIndex = row * GetWidth()*sizeof(RGBA) + col * sizeof(RGBA);
    return *(reinterpret_cast<RGBA *>(((ImageData.GetAllocatedMemory()).get()) + dataIndex));
}
void Image::LoadIntoCache() {
    if (!IsCached()) {
        std::cout << "ImageLoadIntoCache" << std::endl;
        fileLoader->Decode(this);
        IsCached(true);
    }
}

void Image::DeleteFromCache() {
    ImageData.FreeAllocatedMemory();
    IsCached(false);
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
