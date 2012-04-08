#ifndef BRENDER_H
#define BRENDER_H

#include "bimage.h"
#include "bmatrix.h"
#include <vector>
class BRender
{
public:
    BRender();
    void SetScreenSize(int width, int height);
    void FitToScreen(bool fitToScreen);
    void Render(Image * image);
private:
    float GetRatio(Image * image);
    ImageInfo GetNewImageInfo(Image * image, float ratio);
    void RenderImage(Image * image);
    std::pair<float, float> GetCenterPosition(Image * image);
    Image * AllocateRenderBuffer(Image *image, float ratio);

    int width;
    int height;
};


#include "bimageprocess.h"
struct GrayScale {
    void Average(Image * src, Image * dest) {
        BImageProcess procesor;
        procesor.ForEach(src, dest, [](const RGBA & rgba) -> RGBA {
            char gray = (rgba.r + rgba.g + rgba.b) / 3;
            return RGBA(gray, gray, gray);
        });
    }

    void Luminosity(Image * src, Image * dest) {
        BImageProcess procesor;
        procesor.ForEach(src, dest, [](const RGBA & rgba) -> RGBA {
            char gray = (0.21 * rgba.r + 0.71 * rgba.g + 0.07 * rgba.b);
            return RGBA(gray, gray, gray);
        });
    }
    void Lightness(Image * src, Image * dest) {
        BImageProcess procesor;
        procesor.ForEach(src, dest, [](const RGBA & rgba) -> RGBA {
            unsigned char max = std::max<unsigned char>(std::max<unsigned char>(rgba.r, rgba.g), rgba.b);
            unsigned char min = std::min<unsigned char>(std::min<unsigned  char>(rgba.r, rgba.g), rgba.b);
            unsigned char gray = (max + min) /2;
            return RGBA(gray, gray, gray);
        });
    }

};

struct EdgeDetection {
    void Detect(Image * input, Image * output);
};

struct Convolution {
    RGBA KernelsConvolute(Image * source, int row, int col, const std::vector<Matrix<int> >& kernels) {
        std::shared_ptr<char> sourceData = source->ImageData.GetAllocatedMemory();
        RGBA * src = reinterpret_cast<RGBA *>(sourceData.get());

        RGBA value(0,0,0);

            for (int i = 0; i < kernels[0].height; ++i) {
                for (int j = 0; j < kernels[0].width; ++j) {
                    for (int k = 0; k < kernels.size(); ++k) {
                        int srcRow = (row + i) * (source->GetWidth());
                        int kernelValue = kernels[k].Get(i,j);
                        value = value + (src[srcRow + col + j] * kernelValue);
                    }
                }
            }

        return value;
    }

    void Convolute(Image * source, const std::vector<Matrix<int>  >& kernels, Image * output) {
        std::shared_ptr<char> destData = output->ImageData.GetAllocatedMemory();
        RGBA * dest = reinterpret_cast<RGBA *>(destData.get());

        for (int row = 0; row < source->GetHeight() - kernels[0].height; ++row) {
            for (int col = 0; col < source->GetWidth() - kernels[0].width; ++col) {
                RGBA value = KernelsConvolute(source, row, col, kernels);
                dest[(row + 1) * (source->GetWidth()) + col + 1] = value;
            }
        }
    }

    RGBA KernelConvolute(Image * source, int row, int col, const Matrix<int> & kernel) {
        std::shared_ptr<char> sourceData = source->ImageData.GetAllocatedMemory();
        RGBA * src = reinterpret_cast<RGBA *>(sourceData.get());

        RGBA value(0,0,0);
        for (int i = 0; i < kernel.height; ++i) {
            for (int j = 0; j < kernel.width; ++j) {
                int srcRow = (row + i) * (source->GetWidth());
                int kernelValue = kernel.Get(i,j);
                value = value + (src[srcRow + col + j] * kernelValue);
            }
        }
        return value;
    }
};

#endif // BRENDER_H
