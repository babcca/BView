#include "edgedetect.h"

EdgeDetectLaplace5x5::EdgeDetectLaplace5x5() : BFilter()
{
    SetMenuName(L"Edge detector");
    SetMenuItemName(L"Laplace 5x5");
}

void EdgeDetectLaplace5x5::Execute(std::shared_ptr<Image> image, QObject *) {
    std::shared_ptr<Image> out(image->Clone());

    Convolution<int> con;
    con.Convolute(out.get(), GetLaplace(), image.get());
}

std::vector<Matrix<int> > EdgeDetectLaplace5x5::GetLaplace() {
    int laplace5x5[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,24,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    std::vector<Matrix<int> > kernels;
    kernels.push_back(Matrix<int>(5,5,laplace5x5));
    return kernels;
}


EdgeDetectLaplace3x3::EdgeDetectLaplace3x3() : BFilter()
{
    SetMenuName(L"Edge detector");
    SetMenuItemName(L"Laplace 3x3");
}

void EdgeDetectLaplace3x3::Execute(std::shared_ptr<Image> image, QObject *) {
    std::shared_ptr<Image> out(image->Clone());
    Convolution<int> con;
    con.Convolute(out.get(), GetLaplace(), image.get());
}

std::vector<Matrix<int> > EdgeDetectLaplace3x3::GetLaplace() {
    int laplace3x3_1[] = {1,1,1,1,-8,1,1,1,1};
    int laplace3x3_2[] = {0,1,0,1,-4,1,0,1,0};

    std::vector<Matrix<int> > kernels;
    kernels.push_back(Matrix<int>(3,3,laplace3x3_1));
    kernels.push_back(Matrix<int>(3,3,laplace3x3_2));
    return kernels;
}
