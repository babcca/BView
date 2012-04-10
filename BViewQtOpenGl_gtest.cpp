#include "gtest/gtest.h"
#include <algorithm>
#include <iostream>
#include "bdirectory.h"
#include "bsingletoncache.h"
#include "bcache.h"
#include "fileloaderfactory.h"
#include "bmpfileloader.h"
#include "bimage.h"
#include "bimagemanager.h"
#include "brender.h"
#include "bconvolution.h"

#include "functions/imagescale.h"
class JPGFile : ImageFileLoader {
public:
    static ImageFileLoader * CreateInstance() {
        return new JPGFile();
    }
    virtual void Decode(Image *destImage) {
    }
};


TEST(Matrix, Matrix) {
    int a[] = { -1,0,1, -2, 0, 2, -1,0,1};
    Matrix<int> m(3,3,a);
    EXPECT_EQ(3, m.height);
    EXPECT_EQ(3, m.width);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            EXPECT_EQ(a[i*3 + j], m.Get(i,j));
        }
    }

    int b[] = { 1,2,3,4,5,6,7,8,9};
    Matrix<int> n(3,3,b);
    Matrix<int> o(n);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            EXPECT_EQ(n.Get(i,j), o.Get(i,j));
        }
    }
}

TEST(Convolution, Convolute) {

    FileFactory<ImageFileLoader *> fileFactory;
    fileFactory.AddFactory("bmp", [](){ return BMPFileLoader::CreateInstance(); });

    BImageManager imageManager;
    imageManager.SetFileFactory(fileFactory);
    imageManager.LoadDirectory(L".");


    Image * renderImage = new Image(0);
    ImageInfo imageInfo = imageManager.ActualImage->imageInfo;
    renderImage->SetImageInfo(imageInfo);
    renderImage->AllocateMemmory();
    Convolution<int> con;
    int a[] = { -1,0,1, -2, 0, 2, -1,0,1};
    Matrix<int> m(3,3,a);
    std::vector<Matrix<int> > kernels;
    kernels.push_back(m);
    con.Convolute(&imageManager.ActualImage, kernels, renderImage);
    delete renderImage;
}

TEST(Render, Scale) {
    FileFactory<ImageFileLoader *> fileFactory;
    fileFactory.AddFactory("bmp", [](){ return BMPFileLoader::CreateInstance(); });

    BImageManager imageManager;
    imageManager.SetFileFactory(fileFactory);
    imageManager.LoadDirectory(L".");

    tbb::tick_count start_serial = tbb::tick_count::now();
    for (float ratio = 0.2; ratio < 1.0; ratio = ratio + 0.02) {
        ImageScale scaler;
        std::shared_ptr<Image> renderImage = scaler.ScaleSerial(&imageManager.ActualImage, ratio);

    }
    tbb::tick_count stop_serial = tbb::tick_count::now();
    std::cout << "Seril done, parallel start" << std::endl;
    tbb::tick_count start_parallel = tbb::tick_count::now();
    for (float ratio = 0.2; ratio < 1.0; ratio = ratio + 0.02) {
        ImageScale scaler;
        std::shared_ptr<Image> renderImage = scaler.ScaleParallel(&imageManager.ActualImage, ratio);

    }
    tbb::tick_count stop_parallel = tbb::tick_count::now();
    std::cout << "Serial: " << (stop_serial - start_serial).seconds() << std::endl;
    std::cout << "parallel: " << (stop_parallel - start_parallel).seconds() << std::endl;
}

    TEST(Directory, Listing) {
        BDirectory directory;        
        EXPECT_FALSE(directory.file_begin() == directory.file_end());
    }

    TEST(SingletonCache, OneInstance) {
        typedef BSingletonCache<BCache<FileLoader *, cache_traits> > fileCache;
        auto instance = fileCache::Instance();
        EXPECT_EQ(instance, fileCache::Instance());
    }

    TEST(ImageManager, LoadImageDir) {
        FileFactory<ImageFileLoader *> fileFactory;
        fileFactory.AddFactory("bmp", [](){ return BMPFileLoader::CreateInstance(); });
        fileFactory.AddFactory("jpg", [](){ return JPGFile::CreateInstance(); });


        BImageManager imageManager;
        imageManager.SetFileFactory(fileFactory);
        imageManager.LoadDirectory(L".");

        EXPECT_EQ(100,imageManager.ActualImage->GetHeight());
        EXPECT_EQ(100,imageManager.ActualImage->GetWidth());
    }

void TestAll(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
}
