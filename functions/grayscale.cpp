#include "grayscale.h"

void GrayScale::Average(Image * src, Image * dest) {
    BImageProcess::ForEach(src, dest, [](const RGBA & rgba) -> RGBA {
        char gray = (rgba.r + rgba.g + rgba.b) / 3;
        return RGBA(gray, gray, gray);
    });
}

void GrayScale::Luminosity(Image * src, Image * dest) {
    BImageProcess::ForEach(src, dest, [](const RGBA & rgba) -> RGBA {
        char gray = (0.21 * rgba.r + 0.71 * rgba.g + 0.07 * rgba.b);
        return RGBA(gray, gray, gray);
    });
}
void GrayScale::Lightness(Image * src, Image * dest) {
    BImageProcess::ForEach(src, dest, [](const RGBA & rgba) -> RGBA {
        unsigned char max = std::max<unsigned char>(std::max<unsigned char>(rgba.r, rgba.g), rgba.b);
        unsigned char min = std::min<unsigned char>(std::min<unsigned  char>(rgba.r, rgba.g), rgba.b);
        unsigned char gray = (max + min) /2;
        return RGBA(gray, gray, gray);
    });
}

void GrayScale::AverageParallel(Image * src, Image * dest) {
    BImageProcess::ForEachParallel(src, dest, [](const RGBA & rgba) -> RGBA {
        char gray = (rgba.r + rgba.g + rgba.b) / 3;
        return RGBA(gray, gray, gray);
    });
}

void GrayScale::LuminosityParallel(Image * src, Image * dest) {
    BImageProcess::ForEachParallel(src, dest, [](const RGBA & rgba) -> RGBA {
        char gray = (0.21 * rgba.r + 0.71 * rgba.g + 0.07 * rgba.b);
        return RGBA(gray, gray, gray);
    });
}
void GrayScale::LightnessParallel(Image * src, Image * dest) {
    BImageProcess::ForEachParallel(src, dest, [](const RGBA & rgba) -> RGBA {
        unsigned char max = std::max<unsigned char>(std::max<unsigned char>(rgba.r, rgba.g), rgba.b);
        unsigned char min = std::min<unsigned char>(std::min<unsigned  char>(rgba.r, rgba.g), rgba.b);
        unsigned char gray = (max + min) /2;
        return RGBA(gray, gray, gray);
    });
}
