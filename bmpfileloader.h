#ifndef BMPFILELOADER_H
#define BMPFILELOADER_H
#include "fileloader.h"
#include "DataAllocator.h"

class BMPFileLoader : FileLoader {
public:
    BMPFileLoader();
    virtual ~BMPFileLoader() {}
    static FileLoader * CreateInstance();
    DataAllocator fileData;
};

#endif // BMPFILELOADER_H
