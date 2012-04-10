#ifndef BFILTER_H
#define BFILTER_H
#include "bimageprocess.h"

class BFilter {
public:
    virtual void Execute(Image * image) = 0;
    std::wstring GetMenuName() { return menuName; }
protected:
    std::wstring menuName;
};
#endif // BFILTER_H
