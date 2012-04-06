#include "bmpfileloader.h"
#include "bimage.h"
BMPFileLoader::BMPFileLoader()
{
}

BMPFileLoader::~BMPFileLoader() {
}

ImageFileLoader * BMPFileLoader::CreateInstance() {
    return new BMPFileLoader();
}

void BMPFileLoader::Decode(Image *destImage) {
    BmpLib bmp;
    LoadIntoMemory();
    ImageInfo bmpInfo = bmp.InitializeFileHeader(FileData);
    destImage->SetImageInfo(bmpInfo);
    destImage->AllocateMemmory();
    bmp.Decode(FileData, destImage->ImageData);
    ClearMemory();
}
