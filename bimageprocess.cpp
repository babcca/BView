#include "bimageprocess.h"

BImageProcess::BImageProcess()
{
}

void BImageProcess::ForEach(Image *source, Image * destiny, Procesor procesor) {
    int pixels = source->ImageData.GetAllocatedDataSize() / sizeof(RGBA);
    std::shared_ptr<char> imageData = source->ImageData.GetAllocatedMemory();
    RGBA * rgbaData = reinterpret_cast<RGBA *>(imageData.get());

    std::shared_ptr<char> destinyData = destiny->ImageData.GetAllocatedMemory();
    RGBA * oRgbaData = reinterpret_cast<RGBA *>(destinyData.get());

    // Paralel
    for (int position = 0; position < pixels; ++position) {
        oRgbaData[position] = procesor(rgbaData[position]);

    }
}
