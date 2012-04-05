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
    ImageInfo() :  width(0), height(0), bitCount(0), pixelSize(0), pixelFormat(-1), imageSize(0) {}
    ImageInfo(const BMPInfoHeader * header) {
        width = header->biWidth;
        height = header->biHeight;
        bitCount = header->biBitCount;
        pixelSize = bitCount / BYTE_SIZE;
        imageSize = header->biSizeImage;
        pixelFormat =  0x80E0; // GL_BGR
    }
    int width;
    int height;
    int bitCount;
    int pixelSize;
    int imageSize;
    unsigned int pixelFormat; // GLenum
    static const short BYTE_SIZE = 8;
};
#endif // GLOBALSTRUCT_H
