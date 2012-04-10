#include "brender.h"
#include <QGLWidget>
#include <math.h>
#include <assert.h>
#include "bconvolution.h"
#include "functions/imagescale.h"

BRender::BRender() {
    filterManager.RegisterFilter(new GSAverage());
    filterManager.RegisterFilter(new GSLuminosity());
    filterManager.RegisterFilter(new GSLightness());

    filterManager.RegisterFilter(new GSAverageParallel());
    filterManager.RegisterFilter(new GSLuminosityParallel());
    filterManager.RegisterFilter(new GSLightnessParallel());

    filterManager.RegisterFilter(new EdgeDetectLaplace5x5());
    filterManager.RegisterFilter(new EdgeDetectLaplace3x3());
}

void BRender::InitializeMenu(QMenuBar *menuBar) {
     filterManager.RegisterToMenuBar(menuBar);
}

std::shared_ptr<Image> BRender::Render(Image *image, int width, int height) {
    float ratio = GetRatio(image, width, height);
    ImageScale scaler;
    std::shared_ptr<Image> renderImage = scaler.ScaleParallel(image, ratio);
    for (auto filter = filterManager.begin(); filter != filterManager.end(); ++filter) {
        if ((*filter)->IsChecked()) {
            (*filter)->Execute(renderImage);
        }
    }
    return renderImage;

}

std::pair<float, float> BRender::GetCenterPosition(Image * image, int screen_width, int screen_height) {
    int height = image->GetHeight();
    int width = image->GetWidth();
    float pos_x = (screen_width - width) / 2.0;
    float pos_y = screen_height - ((screen_height - height) / 2.0);
    return std::pair<float, float>(pos_x, pos_y);
}

float BRender::GetRatio(Image *image, int width, int height) {
    int i_width = image->GetWidth();
    int i_height = image->GetHeight();
    float ratio = std::min<float>((float) width / i_width, (float) height / i_height);
    return ratio;
}
