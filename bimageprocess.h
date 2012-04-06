#ifndef BIMAGEPROCESS_H
#define BIMAGEPROCESS_H
#include "bimage.h"
#include <functional>

struct ImageRow {
    ImageRow(RGBA * rowData_, int width_) : rowData(rowData_), width(width_) { }
    RGBA * rowData;
    int width;
};

class BImageProcess
{
public:
    typedef std::function<RGBA (const RGBA &)> Procesor;
    typedef std::function<void (int, RGBA &)> EachProcesor;
    typedef std::function<void (int, ImageRow &)> RowProcesor;
    typedef std::function<void (int, RGBA &)> ColProcesor;
    BImageProcess();
    void ForEach(Image *source, Image * destiny, Procesor procesor);
    static void ForEach(Image * source, EachProcesor eachProcesor);

    static void ForEach(ImageRow & imageRow, ColProcesor colProcesor);
    static void ForEachRow(Image * destiny, RowProcesor rowProcesor);


};

#endif // BIMAGEPROCESS_H
