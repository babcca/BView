#ifndef EDGEDETECT_H
#define EDGEDETECT_H
#include <vector>
#include "bfilter.h"
#include "bmatrix.h"

class EdgeDetectLaplace5x5 : public BFilter
{
public:
    EdgeDetectLaplace5x5();
    std::vector<Matrix<int> > GetLaplace();
    virtual void Execute(std::shared_ptr<Image> image);
};

class EdgeDetectLaplace3x3 : public BFilter
{
public:
    EdgeDetectLaplace3x3();
    std::vector<Matrix<int> > GetLaplace();
    virtual void Execute(std::shared_ptr<Image> image);
};




template<typename MatrixType>
struct Convolution {
    RGBA KernelsConvolute(Image * source, int row, int col, const std::vector<Matrix<MatrixType> >& kernels) {
        std::shared_ptr<char> sourceData = source->ImageData.GetAllocatedMemory();
        RGBA * src = reinterpret_cast<RGBA *>(sourceData.get());

        MatrixType value_r = 0;
        MatrixType value_g = 0;
        MatrixType value_b = 0;
        for (int i = 0; i < kernels[0].height; ++i) {
            for (int j = 0; j < kernels[0].width; ++j) {
                for (unsigned int k = 0; k < kernels.size(); ++k) {
                    int srcRow = (row + i) * (source->GetWidth());
                    MatrixType kernelValue = kernels[k].Get(i,j);
                    value_r += (src[srcRow + col + j].r * kernelValue);
                    value_g += (src[srcRow + col + j].g * kernelValue);
                    value_b += (src[srcRow + col + j].b * kernelValue);
                }
            }
        }

        return RGBA(value_r, value_g, value_b);
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


#endif // EDGEDETECT_H
