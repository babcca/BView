#include "bmplib.h"

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
            ImageInfo imageInfo(bmpInfoHeader);
            return imageInfo;
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
        char * compressedDataStart = buffer.get() + data_offset;
        std::shared_ptr<char> decompressedDataStart = output_data_buffer.GetAllocatedMemory();
        std::memcpy(decompressedDataStart.get(), compressedDataStart, output_data_buffer.GetAllocatedDataSize());
	} else {
		throw new std::exception();
	}
}

