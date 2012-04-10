#include "edgedetect.h"

EdgeDetect::EdgeDetect() : BFilter()
{
    SetMenuName(L"Edge detector");
    SetMenuItemName(L"Laplace");
}

void EdgeDetect::Execute(Image *image, Image * out) {
    Convolution<int> con;
    out->SetImageInfo(image->imageInfo);
    out->AllocateMemmory();
    con.Convolute(image, GetLaplace(), out);
}

std::vector<Matrix<int> > EdgeDetect::GetLaplace() {
    int m1[] = {1,1,1,1,-8,1,1,1,1};
    int m2[] = {0,1,0,1,-4,1,0,1,0};
    std::vector<Matrix<int> > kernels;
    kernels.push_back(Matrix<int>(3,3,m1));
    kernels.push_back(Matrix<int>(3,3,m2));
    return kernels;
}
