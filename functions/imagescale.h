#ifndef IMAGESCALE_H
#define IMAGESCALE_H
#include "bimageprocess.h"

class ImageScale
{
public:
    std::shared_ptr<Image> ScaleParallel(Image * source, float ratio /* filters */);
    std::shared_ptr<Image> ScaleSerial(Image * source, float ratio /* filters */);
    ImageInfo GetNewImageInfo(Image * source, float ratio);
    Image * AllocateRenderBuffer(Image * source, float ratio);
    int round(float num);
};

#endif // IMAGESCALE_H
