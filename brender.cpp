#include "brender.h"
#include <QGLWidget>
#include <math.h>
#include <assert.h>
#include "bconvolution.h"
#include "functions/imagescale.h"

BRender::BRender()
{
    filterManager.RegisterFilter(new GSAverage());
    filterManager.RegisterFilter(new GSAverageParallel());
}

void BRender::SetScreenSize(int width, int height) {
    this->width = width;
    this->height = height;
}

void BRender::InitializeMenu(QMenuBar *menuBar) {
    filterManager.RegisterToMenuBar(menuBar);
}

void BRender::Render(Image *image) {
    float ratio = GetRatio(image);
    ImageScale scaler;
    std::shared_ptr<Image> renderImage = scaler.ScaleParallel(image, ratio);
    for (auto filter = filterManager.begin(); filter != filterManager.end(); ++filter) {
        if ((*filter)->IsChecked()) {
            (*filter)->Execute(renderImage.get());
        }
    }
    RenderImage(renderImage.get());

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
