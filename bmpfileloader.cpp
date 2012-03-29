#include "bmpfileloader.h"

BMPFileLoader::BMPFileLoader()
{
}

FileLoader * BMPFileLoader::CreateInstance() {
    return new BMPFileLoader();
}
