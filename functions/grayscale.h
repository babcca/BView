#ifndef GRAYSCALE_H
#define GRAYSCALE_H


#include "bfilter.h"

struct GrayScale {
    void Average(Image * src, Image * dest);
    void Luminosity(Image * src, Image * dest);
    void Lightness(Image * src, Image * dest);

    void AverageParallel(Image * src, Image * dest);
    void LuminosityParallel(Image * src, Image * dest);
    void LightnessParallel(Image * src, Image * dest);
};

class GSAverage : public BFilter {

};

#endif // GRAYSCALE_H
