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
public:
    GSAverage() : BFilter() {
         SetMenuName(L"Grayscale");
         SetMenuItemName(L"Average");
    }
    virtual void Execute(Image *image) {
        BImageProcess::ForEach(image, [](int index, RGBA & rgba) {
            char gray = (rgba.r + rgba.g + rgba.b) / 3;
            rgba = RGBA(gray, gray, gray);
        });
    }
};

class GSAverageParallel : public BFilter {
public:
    GSAverageParallel() : BFilter() {
         SetMenuName(L"Grayscale Parallel");
         SetMenuItemName(L"Average");
    }
    virtual void Execute(Image *image) {
        BImageProcess::ForEachParallel(image, [](int index, RGBA & rgba) {
            char gray = (rgba.r + rgba.g + rgba.b) / 3;
            rgba = RGBA(gray, gray, gray);
        });
    }
};

#endif // GRAYSCALE_H
