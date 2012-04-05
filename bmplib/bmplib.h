#define BMPLIB_EXPORTS
#ifdef BMPLIB_EXPORTS
#define BMPLIB_API __declspec(dllexport)
#else
#define BMPLIB_API __declspec(dllimport)
#endif

#ifndef _BMPLIB_H__
#define _BMPLIB_H__
#include "common.h"

/**
 * @author Petr Babicka
 * I hope, it's thread safe Windows Bitmap decoder
 */
struct BMPLIB_API BmpLib {
	BmpLib();
	void Decode(DataAllocator & input_data_buffer, DataAllocator & output_data_buffer);
    ImageInfo InitializeFileHeader(DataAllocator & file_buffer);
    static const short bmpType = 'MB';
private:
	int data_offset;
};
#endif

