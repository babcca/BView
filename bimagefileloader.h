#ifndef IMAGEFILELOADER_H
#define IMAGEFILELOADER_H
#include "fileloader.h"

class Image;
class ImageFileLoader : public FileLoader {
public:
    virtual void Decode(Image * destImage) = 0;
};

#endif // IMAGEFILELOADER_H
