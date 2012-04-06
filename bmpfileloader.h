#ifndef BMPFILELOADER_H
#define BMPFILELOADER_H
#include "bimagefileloader.h"
#include "bmplib/bmplib.h"

class BMPFileLoader : public ImageFileLoader {
public:
    BMPFileLoader();
    virtual ~BMPFileLoader();
    virtual void Decode(Image *destImage);

    static ImageFileLoader * CreateInstance();
};

#endif // BMPFILELOADER_H
