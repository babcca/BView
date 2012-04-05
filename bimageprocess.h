#ifndef BIMAGEPROCESS_H
#define BIMAGEPROCESS_H
#include "bimage.h"
#include <functional>

class BImageProcess
{
public:
    typedef std::function<RGBA (const RGBA &)> Procesor;
    BImageProcess();
    void ForEach(Image *source, Image * destiny, Procesor Procesor);
};

#endif // BIMAGEPROCESS_H
