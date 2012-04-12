#ifndef GRAYSCALE_H
#define GRAYSCALE_H

#include "bfilter.h"

class GSAverage : public BFilter {
public:
    GSAverage() : BFilter() {
         SetMenuName(L"&Grayscale");
         SetMenuItemName(L"Average");
    }
    virtual void Execute(std::shared_ptr<Image> image, QObject *) {
        BImageProcess::ForEach(image.get(), [](int, RGBA & rgba) {
            unsigned char gray = (rgba.r + rgba.g + rgba.b) / 3;
            rgba = RGBA(gray, gray, gray);
        });
    }
};


class GSLuminosity : public BFilter {
public:
    GSLuminosity() : BFilter() {
         SetMenuName(L"&Grayscale");
         SetMenuItemName(L"Luminosity");
    }
    virtual void Execute(std::shared_ptr<Image> image, QObject *) {
        BImageProcess::ForEach(image.get(), [](int, RGBA & rgba) {
            unsigned char gray = (0.21 * rgba.r + 0.71 * rgba.g + 0.07 * rgba.b);
            rgba = RGBA(gray, gray, gray);
        });
    }
};


class GSLightness : public BFilter {
public:
    GSLightness() : BFilter() {
         SetMenuName(L"&Grayscale");
         SetMenuItemName(L"Lightness");
    }
    virtual void Execute(std::shared_ptr<Image> image, QObject *) {
        BImageProcess::ForEach(image.get(), [](int, RGBA & rgba) {
            unsigned char max = std::max<unsigned char>(std::max<unsigned char>(rgba.r, rgba.g), rgba.b);
            unsigned char min = std::min<unsigned char>(std::min<unsigned char>(rgba.r, rgba.g), rgba.b);
            unsigned char gray = (max + min) /2;
            rgba = RGBA(gray, gray, gray);
        });
    }
};



class GSAverageParallel : public BFilter {
public:
    GSAverageParallel() : BFilter() {
         SetMenuName(L"Grayscale &Parallel");
         SetMenuItemName(L"Average");
    }
    virtual void Execute(std::shared_ptr<Image> image, QObject *) {
        BImageProcess::ForEachParallel(image.get(), [](int, RGBA & rgba) {
            unsigned char gray = (rgba.r + rgba.g + rgba.b) / 3;
            rgba = RGBA(gray, gray, gray);
        });
    }
};


class GSLuminosityParallel : public BFilter {
public:
    GSLuminosityParallel() : BFilter() {
         SetMenuName(L"Grayscale &Parallel");
         SetMenuItemName(L"Luminosity");
    }
    virtual void Execute(std::shared_ptr<Image> image, QObject *) {
        BImageProcess::ForEachParallel(image.get(), [](int, RGBA & rgba) {
            unsigned char gray = (0.21 * rgba.r + 0.71 * rgba.g + 0.07 * rgba.b);
            rgba = RGBA(gray, gray, gray);
        });
    }
};


class GSLightnessParallel : public BFilter {
public:
    GSLightnessParallel() : BFilter() {
         SetMenuName(L"Grayscale &Parallel");
         SetMenuItemName(L"Lightness");
    }
    virtual void Execute(std::shared_ptr<Image> image, QObject *) {
        BImageProcess::ForEachParallel(image.get(), [](int, RGBA & rgba) {
            unsigned char max = std::max<unsigned char>(std::max<unsigned char>(rgba.r, rgba.g), rgba.b);
            unsigned char min = std::min<unsigned char>(std::min<unsigned char>(rgba.r, rgba.g), rgba.b);
            unsigned char gray = (max + min) /2;
            rgba = RGBA(gray, gray, gray);
        });
    }
};

#include "QGLShader"
class GSLightnessGPU : public BFilter {
public:
    GSLightnessGPU() : BFilter(), program(0) {
         SetMenuName(L"Grayscale &GPU");
         SetMenuItemName(L"Lightness");
         //InitializeShader();


    }
    virtual void Execute(std::shared_ptr<Image> image, QObject * parent = 0) {
        std::cout << "GPU execute" << std::endl;
        if (program ==0) {
            InitializeShader(parent);
        }
        program->bind();
    }

protected:
    virtual void Initialize() {
        std::cout << "Init" << std::endl;
        if (program != 0) {
            program->bind();
        }
    }

    virtual void Release() {
        std::cout << "Release" << std::endl;
        if (program != 0) {
            program->release();
        }
    }
private:
    void InitializeShader(QObject * parent = 0) {
        std::cout << "GPU init" << std::endl;
        QGLShader * shader = new QGLShader(QGLShader::Fragment, parent);
        shader->compileSourceFile("./grayscale.frag");
        program = new QGLShaderProgram(parent);
        program->addShader(shader);
        program->link();
    }

    QGLShaderProgram * program;
};

#endif // GRAYSCALE_H
