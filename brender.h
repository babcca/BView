#ifndef BRENDER_H
#define BRENDER_H

#include "bfunctionmanager.h"
#include <vector>
class BRender
{
public:
    BRender();
    void SetScreenSize(int width, int height);
    /** @deprecated */
    //void FitToScreen(bool fitToScreen);

    void Render(Image * image);
    void InitializeMenu(QMenuBar * menuBar);
private:
    float GetRatio(Image * image);
    void RenderImage(Image * image);
    std::pair<float, float> GetCenterPosition(Image * image);
    /** @deprecated */
    //Image * AllocateRenderBuffer(Image *image, float ratio);
    /** @deprecated */
    //ImageInfo GetNewImageInfo(Image * image, float ratio);

    int width;
    int height;
    BFilterManager filterManager;
};



#include "bmatrix.h"
struct EdgeDetection {
    void Detect(Image * input, Image * output);
};
template<typename MatrixType>
struct Convolution {
    RGBA KernelsConvolute(Image * source, int row, int col, const std::vector<Matrix<MatrixType> >& kernels) {
        std::shared_ptr<char> sourceData = source->ImageData.GetAllocatedMemory();
        RGBA * src = reinterpret_cast<RGBA *>(sourceData.get());

        RGBA value(0,0,0);

            for (int i = 0; i < kernels[0].height; ++i) {
                for (int j = 0; j < kernels[0].width; ++j) {
                    for (unsigned int k = 0; k < kernels.size(); ++k) {
                        int srcRow = (row + i) * (source->GetWidth());
                        MatrixType kernelValue = kernels[k].Get(i,j);
                        value = value + (src[srcRow + col + j] * kernelValue);
                    }
                }
            }

        return value;
    }

    void Convolute(Image * source, const std::vector<Matrix<MatrixType>  >& kernels, Image * output) {
        std::shared_ptr<char> destData = output->ImageData.GetAllocatedMemory();
        RGBA * dest = reinterpret_cast<RGBA *>(destData.get());

        for (int row = 0; row < source->GetHeight() - kernels[0].height; ++row) {
            for (int col = 0; col < source->GetWidth() - kernels[0].width; ++col) {
                RGBA value = KernelsConvolute(source, row, col, kernels);
                dest[(row + 1) * (source->GetWidth()) + col + 1] = value;
            }
        }
    }


    RGBA KernelConvolute(Image * source, int row, int col, const Matrix<MatrixType> & kernel) {
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
