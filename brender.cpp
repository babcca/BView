#include "brender.h"
#include <QGLWidget>
#include <math.h>
#include <assert.h>
#include "bconvolution.h"
#include "functions/grayscale.h"
#include "functions/imagescale.h"
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


        // Gauss odstraneni sumu
        float gauss[] = {1,2,1,2,4,2,1,2,1};
        Matrix<float> gauss_matrix(3,3,gauss);
        gauss_matrix *= (1/16.0);
        std::vector<Matrix<float> > sum;
        sum.push_back(gauss_matrix);
        // laplace full
        int e[] = {1,1,1,1,-8,1,1,1,1};
        // laplace
        int f[] = {0,1,0,1,-4,1,0,1,0};
        std::vector<Matrix<int> > kernels;
        Matrix<int> laplaceKernel(3,3,e);
        kernels.push_back(laplaceKernel);
        Convolution<int> convolution;
        Convolution<float> convolution_f;

        Image * edge = new Image(0);
        edge->SetImageInfo(image->imageInfo);
        edge->AllocateMemmory();


        Image * redukce_sum = new Image(0);
        redukce_sum->SetImageInfo(image->imageInfo);
        redukce_sum->AllocateMemmory();


        Image * redukce_sum_out = new Image(0);
        redukce_sum_out->SetImageInfo(image->imageInfo);
        redukce_sum_out->AllocateMemmory();

        GrayScale grayScale;

        //grayScale.LuminosityParallel(image, edge);
        //convolution_f.Convolute(image, sum, redukce_sum);
        convolution.Convolute(image, kernels, redukce_sum);


        ImageScale scaler;
        std::shared_ptr<Image> renderImage = scaler.ScaleParallel(redukce_sum, ratio);

        RenderImage(renderImage.get());
        delete edge;
        delete redukce_sum;
        delete redukce_sum_out;
    } else {
        Image * edge = new Image(0);
        edge->SetImageInfo(image->imageInfo);
        edge->AllocateMemmory();
        // sobel
        int a[] = { -1,0,1, -2, 0, 2, -1,0,1};
        int b[] = { 1,2,1, 0,0,0, -1,-2,-1};
        int c[] = { -2,-1,0, -1, 0, 1, 0,1,2 };
        int d[] = { 0,1,2,-1,0,1,-2,-1,0};
        // laplace full
        int e[] = {1,1,1,1,-8,1,1,1,1};
        // laplace
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
        g.LuminosityParallel(image, image);
        Convolution<int> convolution;

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
