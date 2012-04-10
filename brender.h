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


#endif // BRENDER_H
