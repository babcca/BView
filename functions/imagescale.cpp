#include "imagescale.h"

std::shared_ptr<Image>  ImageScale::ScaleParallel(Image * source, float ratio /* filters */) {
    Image * output = AllocateRenderBuffer(source, ratio);
    int srcWidth = source->GetWidth();
    int srcHeight = source->GetHeight();
    int destWidth = output->GetWidth();
    int destHeight = output->GetHeight();

    float rowRatio = srcHeight / (float) destHeight;
    float colRatio = srcWidth / (float) destWidth;

    BImageProcess::ForEachRowParallel(output, [=](int row_index, ImageRow & row) {
        int rowIndex = round(row_index*rowRatio);
        BImageProcess::ForEachInRow(row, [=](int col_index, RGBA & outPixel) {
            int colIndex = round(col_index * colRatio);
            outPixel = source->GetPixel(rowIndex, colIndex);
        });
    });
    return std::shared_ptr<Image>(output);
}

std::shared_ptr<Image> ImageScale::ScaleSerial(Image * source, float ratio /* filters */) {
    Image * output = AllocateRenderBuffer(source, ratio);
    int srcWidth = source->GetWidth();
    int srcHeight = source->GetHeight();
    int destWidth = output->GetWidth();
    int destHeight = output->GetHeight();

    float rowRatio = srcHeight / (float) destHeight;
    float colRatio = srcWidth / (float) destWidth;

    BImageProcess::ForEachRowSerial(output, [=](int row_index, ImageRow & row) {
        int rowIndex = round(row_index*rowRatio);
        BImageProcess::ForEachInRow(row, [=](int col_index, RGBA & outPixel) {
            int colIndex = round(col_index * colRatio);
            outPixel = source->GetPixel(rowIndex, colIndex);
        });
    });
    return std::shared_ptr<Image>(output);
}

ImageInfo ImageScale::GetNewImageInfo(Image * source, float ratio) {
    ImageInfo imageInfo =  source->imageInfo;
    if (ratio < 1.0) {
        imageInfo.width = floor(imageInfo.width * ratio);
        imageInfo.height = floor(imageInfo.height * ratio);
        imageInfo.imageSize = (imageInfo.width) * (imageInfo.height ) * sizeof(RGBA);
    }
    return imageInfo;
}

Image * ImageScale::AllocateRenderBuffer(Image * source, float ratio) {
    ImageInfo imageInfo = GetNewImageInfo(source, ratio);
    Image * outputImage = new Image(0);
    outputImage->SetImageInfo(imageInfo);
    outputImage->AllocateMemmory();
    return outputImage;
}
int ImageScale::round(float num) {
    return (int) floor(num + 0.5);
}
