#include "bmplib.h"
#include <iostream>
/// <summary>
/// Dokumentace datovych struktur
///		http://msdn.microsoft.com/en-us/library/dd183376
///		http://msdn.microsoft.com/en-us/library/dd183374(v=vs.85).aspx
/// </summary>
BmpLib::BmpLib() : data_offset(0)
{ }

ImageInfo BmpLib::InitializeFileHeader(DataAllocator & file_buffer) {
	if (file_buffer.IsMemoryAllocated()) {
        // buffer contains pointer to bitmap file copied into memmory
        std::shared_ptr<char> memory = file_buffer.GetAllocatedMemory();
		// Type cast to file header
        BITMAPFILEHEADER * bmpFileHeader = (BITMAPFILEHEADER *) memory.get();
		if (bmpFileHeader->bfType == bmpType) {
            data_offset =  bmpFileHeader->bfOffBits;
            // After file header is info header
            BMPInfoHeader * bmpInfoHeader = (BMPInfoHeader *) (memory.get()+sizeof(BITMAPFILEHEADER));
            if (bmpInfoHeader->biBitCount == 24) {
                ImageInfo imageInfo(bmpInfoHeader);
                imageInfo.imageSize = imageInfo.width * imageInfo.height * sizeof(RGBA);
                return imageInfo;
            } else {
                throw new std::exception();
            }
		} else {
			throw new std::exception();
		}
    } else {
        throw new std::exception();
    }
}

void BmpLib::Decode(DataAllocator & input_data_buffer, DataAllocator & output_data_buffer) {
	if (output_data_buffer.IsMemoryAllocated()) {
		// Uncompress commepresed data start
        std::shared_ptr<char> buffer = input_data_buffer.GetAllocatedMemory();
        char * sourceData = buffer.get() + data_offset;

        std::shared_ptr<char> decompressedDataStart = output_data_buffer.GetAllocatedMemory();
        char * destDataStart = decompressedDataStart.get();
        RGBA * destData = reinterpret_cast<RGBA *>(destDataStart);

        BMPInfoHeader * bmpInfoHeader = reinterpret_cast<BMPInfoHeader *>(buffer.get()+sizeof(BITMAPFILEHEADER));
        int width = bmpInfoHeader->biWidth;
        int height = bmpInfoHeader->biHeight;

        unsigned int lineLength = static_cast<unsigned int>((ceil((width * 3)/4.0))*4);
        unsigned int offset = lineLength - 3*width;

        for (int row = 0; row < height; ++row) {
            for (int col = 0; col < width; ++col) {
                char b = (*sourceData++);
                char g = (*sourceData++);
                char r = (*sourceData++);
                *destData++ = RGBA(r,g,b);
            }
            sourceData += offset;
        }

	} else {
		throw new std::exception();
	}
}

