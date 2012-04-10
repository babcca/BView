#ifndef GRAYSCALE_H
#define GRAYSCALE_H

#include "bfilter.h"

class GSAverage : public BFilter {
public:
    GSAverage() : BFilter() {
         SetMenuName(L"&Grayscale");
         SetMenuItemName(L"Average");
    }
    virtual void Execute(std::shared_ptr<Image> image) {
        BImageProcess::ForEach(image.get(), [](int, RGBA & rgba) {
            unsigned char gray = (rgba.r + rgba.g + rgba.b) / 3;
            rgba = RGBA(gray, gray, gray);
        });
    }
};


class GSLuminosity : public BFilter {
public:
    GSLuminosity() : BFilter() {
         SetMenuName(L"&Grayscale");
         SetMenuItemName(L"Luminosity");
    }
    virtual void Execute(std::shared_ptr<Image> image) {
        BImageProcess::ForEach(image.get(), [](int, RGBA & rgba) {
            unsigned char gray = (0.21 * rgba.r + 0.71 * rgba.g + 0.07 * rgba.b);
            rgba = RGBA(gray, gray, gray);
        });
    }
};


class GSLightness : public BFilter {
public:
    GSLightness() : BFilter() {
         SetMenuName(L"&Grayscale");
         SetMenuItemName(L"Lightness");
    }
    virtual void Execute(std::shared_ptr<Image> image) {
        BImageProcess::ForEach(image.get(), [](int, RGBA & rgba) {
            unsigned char max = std::max<unsigned char>(std::max<unsigned char>(rgba.r, rgba.g), rgba.b);
            unsigned char min = std::min<unsigned char>(std::min<unsigned char>(rgba.r, rgba.g), rgba.b);
            unsigned char gray = (max + min) /2;
            rgba = RGBA(gray, gray, gray);
        });
    }
};



class GSAverageParallel : public BFilter {
public:
    GSAverageParallel() : BFilter() {
         SetMenuName(L"Grayscale &Parallel");
         SetMenuItemName(L"Average");
    }
    virtual void Execute(std::shared_ptr<Image> image) {
        BImageProcess::ForEachParallel(image.get(), [](int, RGBA & rgba) {
            unsigned char gray = (rgba.r + rgba.g + rgba.b) / 3;
            rgba = RGBA(gray, gray, gray);
        });
    }
};


class GSLuminosityParallel : public BFilter {
public:
    GSLuminosityParallel() : BFilter() {
         SetMenuName(L"Grayscale &Parallel");
         SetMenuItemName(L"Luminosity");
    }
    virtual void Execute(std::shared_ptr<Image> image) {
        BImageProcess::ForEachParallel(image.get(), [](int, RGBA & rgba) {
            unsigned char gray = (0.21 * rgba.r + 0.71 * rgba.g + 0.07 * rgba.b);
            rgba = RGBA(gray, gray, gray);
        });
    }
};


class GSLightnessParallel : public BFilter {
public:
    GSLightnessParallel() : BFilter() {
         SetMenuName(L"Grayscale &Parallel");
         SetMenuItemName(L"Lightness");
    }
    virtual void Execute(std::shared_ptr<Image> image) {
        BImageProcess::ForEachParallel(image.get(), [](int, RGBA & rgba) {
            unsigned char max = std::max<unsigned char>(std::max<unsigned char>(rgba.r, rgba.g), rgba.b);
            unsigned char min = std::min<unsigned char>(std::min<unsigned char>(rgba.r, rgba.g), rgba.b);
            unsigned char gray = (max + min) /2;
            rgba = RGBA(gray, gray, gray);
        });
    }
};

#endif // GRAYSCALE_H
