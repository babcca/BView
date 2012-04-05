#ifndef BRENDER_H
#define BRENDER_H

#include "bimage.h"

class BRender
{
public:
    BRender();
    void SetScreenSize(int width, int height);
    void FitToScreen(bool fitToScreen);
    void Render(Image * image);
private:
    float GetRatio(Image * image);
    ImageInfo GetNewImageInfo(Image * image, float ratio);
    void RenderImage(Image * image);
    std::pair<float, float> GetCenterPosition(Image * image);
    Image * AllocateRenderBuffer(Image *image, float ratio);

    int width;
    int height;
};

struct BGR {
    char g;
    char b;
    char r;
};

struct Scale {
    void ScaleRect(Image * input, Image * output, float ratio);
private:
    void ScaleLine(BGR * src, BGR * dest, int srcWidth, int destWidth);

};

#include <memory>
template<typename Type>
struct Matrix {
    Matrix(int width_, int height_, Type * values)
        : width(width_), height(height_) {
        matrix = new Type[width*height];
        std::memcpy(matrix, values, width*height*sizeof(Type));
        /*
        for (int i = 0; i < width*height; ++i) {
            matrix[i] = values[i];
        }
        */

    }

    ~Matrix() {
        if (matrix != 0) {
            delete matrix;
            matrix = 0;
        }
    }
    /*
    {
        if (*this != matrix) {
            if (this->matrix != 0) {
                delete this->matrix;
                this->matrix = 0;
            }
            width = matrix.width;
            height = matrix.height;
            std::memcpy(this->matrix, matrix, width*height);
        }
        return *this;
    }
    */
    const Type Get(int row, int col) const {
        int index = (row * width) + col;
        Type v = matrix[index];
        return v;
    }

    int width;
    int height;

private:
    Matrix (const Matrix &);
    Matrix & operator= (const Matrix & matrix);
    Type * matrix;
};

struct EdgeDetection {
    void Detect(Image * input, Image * output);
};

struct Convolution {
    void Convolute(Image * source, const Matrix<int> & kernel, Image * output) {


        std::shared_ptr<char> destData = output->ImageData.GetAllocatedMemory();
        char * dest = destData.get();

        for (int row = 0; row < source->GetHeight() * 3 - kernel.height; ++row) {
            for (int col = 0; col < source->GetWidth() * 3 - kernel.width; ++col) {
                int value = KernelConvolute(source, row, col, kernel);
                qDebug("a %d = %d", col,  source->GetWidth());
                if (col == source->GetWidth()) {
                    int b = 12*221;

                }
                dest[(row + 1) * (source->GetWidth() * 3) + col + 1] = (unsigned char) abs(value);

            }
        }
    }

    int KernelConvolute(Image * source, int row, int col, const Matrix<int> & kernel) {
        std::shared_ptr<char> sourceData = source->ImageData.GetAllocatedMemory();
        char * src = sourceData.get();
        int value = 0;
        for (int i = 0; i < kernel.height; ++i) {
            for (int j = 0; j < kernel.width; ++j) {
                int srcRow = (row + i) * (source->GetWidth() * 3);
                int kernelValue = kernel.Get(i,j);
                value += src[srcRow + col + j] * kernelValue;
            }
        }
        return value;
    }
};

#endif // BRENDER_H
