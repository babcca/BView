#ifndef BMPFILELOADER_H
#define BMPFILELOADER_H
#include "bimagefileloader.h"
#include "bmplib/bmplib.h"

class BMPFileLoader : public ImageFileLoader {
public:
    BMPFileLoader();
    virtual ~BMPFileLoader() {}
    static ImageFileLoader * CreateInstance();
    virtual void Decode(Image *destImage);

};

#endif // BMPFILELOADER_H
