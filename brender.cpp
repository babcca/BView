#include "brender.h"
#include <QGLWidget>
#include <math.h>
#include <assert.h>
#include "bconvolution.h"
BRender::BRender()
{
}

void BRender::SetScreenSize(int width, int height) {
    this->width = width;
    this->height = height;
}

void BRender::Render(Image *image) {
    float ratio =  GetRatio(image);
    ratio = floor(ratio*100)/100;
    qDebug("%f", ratio);
    if (ratio < 1.0) {
        //Image * renderImage = AllocateRenderBuffer(image, ratio);
        Scaler scaler;
        std::shared_ptr<Image> renderImage = scaler.ScaleParallel(image, ratio);
        RenderImage(renderImage.get());
        //delete renderImage;
    } else {
        RenderImage(image);
        return;
        Image * edge = new Image(0);
        edge->SetImageInfo(image->imageInfo);
        edge->AllocateMemmory();
        int a[] = { -1,0,1, -2, 0, 2, -1,0,1};
        int b[] = { 1,2,1, 0,0,0, -1,-2,-1};
        int c[] = { -2,-1,0, -1, 0, 1, 0,1,2 };
        int d[] = { 0,1,2,-1,0,1,-2,-1,0};
        int e[] = {1,1,1,1,-8,1,1,1,1};
        int f[] = {0,1,0,1,-4,1,0,1,0};
        std::vector<Matrix<int> > kernels;
        Matrix<int> m(3,3,a);
        Matrix<int> n(3,3,b);
        Matrix<int> o(3,3,c);
        Matrix<int> p(3,3,d);
        Matrix<int> q(3,3,f);
        //kernels.push_back(m);
        //kernels.push_back(n);
        //kernels.push_back(o);
        //kernels.push_back(p);
        kernels.push_back(q);
        GrayScale g;
        g.Luminosity(image, image);
        Convolution convolution;
        convolution.Convolute(image, kernels, edge);
        RenderImage(edge);
        delete edge;
    }
}

std::pair<float, float> BRender::GetCenterPosition(Image * image) {
    int height = image->GetHeight();
    int width = image->GetWidth();
    float pos_x = (this->width - width) / 2.0;
    float pos_y = this->height - ((this->height - height) / 2.0);
    return std::pair<float, float>(pos_x, pos_y);
}

void BRender::RenderImage(Image *image) {
    GrayScale g;
    g.Luminosity(image, image);
    int height = image->GetHeight();
    int width = image->GetWidth();
    int format = image->GetPixelFormat();
    std::shared_ptr<char> raw = image->ImageData.GetAllocatedMemory();
    std::pair<float, float> centerPosition = GetCenterPosition(image);
    glRasterPos2i(centerPosition.first, centerPosition.second);
    glDrawPixels(width, height, format, GL_UNSIGNED_BYTE, raw.get());
}

float BRender::GetRatio(Image *image) {
    int i_width = image->GetWidth();
    int i_height = image->GetHeight();
    float ratio = std::min<float>((float) width / i_width, (float) height / i_height);
    return ratio;
}


/** @deprecated */
Image * BRender::AllocateRenderBuffer(Image * image, float ratio) {
    ImageInfo imageInfo = GetNewImageInfo(image, ratio);
    Image * renderImage = new Image(0);
    renderImage->SetImageInfo(imageInfo);
    renderImage->AllocateMemmory();
    return renderImage;
}


/** @deprecated */
ImageInfo BRender::GetNewImageInfo(Image *image, float ratio) {
    ImageInfo imageInfo = image->imageInfo;
    // Bitmapa ma zarovnani radky na nasobky 4 (do 32 bit intu)
    imageInfo.width = floor(imageInfo.width * ratio);
    imageInfo.height = floor(imageInfo.height * ratio);
    imageInfo.imageSize = (imageInfo.width) * (imageInfo.height ) * 4;
    return imageInfo;
}
