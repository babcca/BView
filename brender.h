#ifndef BRENDER_H
#define BRENDER_H

#include <vector>
#include "bimage.h"
#include "bfunctionmanager.h"
class BRender
{
public:
    BRender();
    void SetScreenSize(int width, int height);
    std::shared_ptr<Image> Render(Image * image, int width, int height, QObject * parent = 0);
    std::pair<float, float> GetCenterPosition(Image * image, int screen_width, int screen_height);
    void InitializeMenu(QMenuBar * menuBar);
    BFilterManager filterManager;
private:
    float GetRatio(Image * image, int width, int height);
    void RenderImage(Image * image);

    int width;
    int height;
};

#endif // BRENDER_H
