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


void BImageProcess::ForEachParallel(Image *source, Image * destiny, Procesor procesor) {
    int pixels = source->ImageData.GetAllocatedDataSize() / sizeof(RGBA);
    std::shared_ptr<char> imageData = source->ImageData.GetAllocatedMemory();
    RGBA * rgbaData = reinterpret_cast<RGBA *>(imageData.get());

    std::shared_ptr<char> destinyData = destiny->ImageData.GetAllocatedMemory();
    RGBA * oRgbaData = reinterpret_cast<RGBA *>(destinyData.get());

    tbb::parallel_for(tbb::blocked_range<size_t>(0, pixels), [=](tbb::blocked_range<size_t> & range) {
        for (size_t row = range.begin(); row != range.end(); ++row) {
            oRgbaData[row] = procesor(rgbaData[row]);
        }

    });
}



void BImageProcess::ForEachInRow(ImageRow & imageRow, ColProcesor colProcesor) {
    for (int col = 0; col < imageRow.width; ++col) {
        colProcesor(col, imageRow.rowData[col]);
    }
}

void BImageProcess::ForEachRowSerial(Image *destiny, RowProcesor rowProcesor) {
    std::shared_ptr<char> destinyMemory = destiny->ImageData.GetAllocatedMemory();
    RGBA * destinyData = reinterpret_cast<RGBA *>(destinyMemory.get());

    for (int row = 0; row < destiny->GetHeight(); ++row) {
        RGBA * rowDataPointer = destinyData + row*(destiny->GetWidth());
        ImageRow rowData(rowDataPointer, destiny->GetWidth());
        rowProcesor(row, rowData);
    }
}

void BImageProcess::ForEachRowParallel(Image *destiny, RowProcesor rowProcesor) {
    std::shared_ptr<char> destinyMemory = destiny->ImageData.GetAllocatedMemory();
    RGBA * destinyData = reinterpret_cast<RGBA *>(destinyMemory.get());

    tbb::parallel_for(tbb::blocked_range<size_t>(0, destiny->GetHeight()), [=](tbb::blocked_range<size_t> & range) {
        for (size_t row = range.begin(); row != range.end(); ++row) {
            RGBA * rowDataPointer = destinyData + row*(destiny->GetWidth());
            ImageRow rowData(rowDataPointer, destiny->GetWidth());
            rowProcesor(row, rowData);
        }
    });
}
