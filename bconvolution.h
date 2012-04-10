#ifndef BCONVOLUTION_H
#define BCONVOLUTION_H
#include <vector>
#include <cmath>
#include "bmatrix.h"
#include "bimageprocess.h"

class BConvolution {
public:
    BConvolution();
    void Convolute(Image * source, const std::vector<Matrix<int> >& kernels, Image * output);
    RGBA KernelsConvolute(Image * source, int row, int col, const std::vector<Matrix<int> >& kernels);
    RGBA KernelConvolute(Image * source, int row, int col, const Matrix<int> & kernel);
};



#endif // BCONVOLUTION_H
