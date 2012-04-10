#ifndef BIMAGEPROCESS_H
#define BIMAGEPROCESS_H
#include "bimage.h"
#include <functional>
#include "tbb/parallel_for.h"
#include "tbb/parallel_reduce.h"
#include "tbb/blocked_range.h"
#include "tbb/tick_count.h"

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

    static void ForEach(Image *source, Image * destiny, Procesor procesor);
    static void ForEachParallel(Image *source, Image * destiny, Procesor procesor);

    static void ForEach(Image * source, EachProcesor eachProcesor);

    static void ForEachInRow(ImageRow & imageRow, ColProcesor colProcesor);
    static void ForEachRowSerial(Image * destiny, RowProcesor rowProcesor);
    static void ForEachRowParallel(Image * destiny, RowProcesor rowProcesor);


};

#endif // BIMAGEPROCESS_H
