#include "bmpfileloader.h"
#include "bimage.h"
BMPFileLoader::BMPFileLoader()
{
}

ImageFileLoader * BMPFileLoader::CreateInstance() {
    return new BMPFileLoader();
}

void BMPFileLoader::Decode(Image *destImage) {
    BmpLib bmp;
    ImageInfo bmpInfo = bmp.InitializeFileHeader(FileData);
    destImage->SetImageInfo(bmpInfo);
    destImage->AllocateMemmory();
    bmp.Decode(FileData, destImage->ImageData);

}
