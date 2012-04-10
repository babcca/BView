#ifndef GLOBALSTRUCT_H
#define GLOBALSTRUCT_H

struct BMPInfoHeader {
  unsigned long biSize;
  long biWidth;
  long biHeight;
  unsigned short biPlanes;
  unsigned short biBitCount;
  unsigned long biCompression;
  unsigned long biSizeImage;
  long biXPelsPerMeter;
  long biYPelsPerMeter;
  unsigned long biClrUsed;
  unsigned long biClrImportant;
};

struct ImageInfo {
    static const unsigned int RGBA = 0x1908;
    static const short PIXEL_SIZE = 4;

    ImageInfo() :  width(0), height(0), bitCount(0), pixelSize(0), pixelFormat(-1), imageSize(0) {}
    ImageInfo(const BMPInfoHeader * header) {
        width = header->biWidth;
        height = header->biHeight;
        bitCount = header->biBitCount;
        imageSize = header->biSizeImage;
        pixelFormat =  this->RGBA; // GL_BGR
        pixelSize = PIXEL_SIZE;
    }
    int width;
    int height;
    int bitCount;
    int pixelSize;
    int imageSize;
    unsigned int pixelFormat; // GLenum

};

struct BGR {
    char g;
    char b;
    char r;
};

struct RGBA {
    RGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    template<typename Type>
    RGBA(Type r, Type g, Type b, Type a = 255) {
        this->r = (unsigned char) (std::max<Type>(0, std::min<Type>(r, 255)));
        this->g = (unsigned char) (std::max<Type>(0, std::min<Type>(g, 255)));
        this->b = (unsigned char) (std::max<Type>(0, std::min<Type>(b, 255)));
        this->a = (unsigned char) (std::max<Type>(0, std::min<Type>(a, 255)));
    }

    RGBA(const BGR & bgr) {
        this->r = bgr.r;
        this->g = bgr.g;
        this->b = bgr.b;
        this->a = 150;
    }

    RGBA operator*(const int value) {
        return RGBA(r*value, g*value, b*value);
    }

    RGBA operator*(const float value) {
        return RGBA(r*value, g*value, b*value);
    }

    RGBA operator+(const RGBA & rgba) {
        return RGBA(r+rgba.r,g+rgba.g,b+rgba.b);
    }

    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

#endif // GLOBALSTRUCT_H
