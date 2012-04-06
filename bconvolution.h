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


class Scaler {
public:
    std::shared_ptr<Image> Scale(Image * source, float ratio /* filters */) {
        Image * output = AllocateRenderBuffer(source, ratio);
        int srcWidth = source->GetWidth();
        int srcHeight = source->GetHeight();
        int destWidth = output->GetWidth();
        int destHeight = output->GetHeight();

        float rowRatio = srcHeight / (float) destHeight;
        float colRatio = srcWidth / (float) destWidth;

        BImageProcess::ForEachRow(output, [=](int row_index, ImageRow & row) {
            int rowIndex = round(row_index*rowRatio);
            BImageProcess::ForEach(row, [=](int col_index, RGBA & outPixel) {
                int colIndex = round(col_index * colRatio);
                outPixel = source->GetPixel(rowIndex, colIndex);
            });
        });
        return std::shared_ptr<Image>(output);
    }

    ImageInfo GetNewImageInfo(Image * source, float ratio) {
        ImageInfo imageInfo =  source->imageInfo;
        imageInfo.width = floor(imageInfo.width * ratio);
        imageInfo.height = floor(imageInfo.height * ratio);
        imageInfo.imageSize = (imageInfo.width) * (imageInfo.height ) * sizeof(RGBA);
        return imageInfo;
    }

    Image * AllocateRenderBuffer(Image * source, float ratio) {
        ImageInfo imageInfo = GetNewImageInfo(source, ratio);
        Image * outputImage = new Image(0);
        outputImage->SetImageInfo(imageInfo);
        outputImage->AllocateMemmory();
        return outputImage;
    }
    int round(float num) {
        return (int) floor(num + 0.5);
    }

};


#endif // BCONVOLUTION_H
