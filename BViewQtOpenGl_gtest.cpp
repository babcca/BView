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
class JPGFile : ImageFileLoader {
public:
    static ImageFileLoader * CreateInstance() {
        return new JPGFile();
    }
    virtual void Decode(Image *destImage) {
    }
};

ImageInfo GetNewImageInfo(Image *image, float ratio) {
    ImageInfo imageInfo = image->imageInfo;
    imageInfo.width = imageInfo.width * ratio;
    imageInfo.height = imageInfo.height * ratio;
    imageInfo.imageSize = imageInfo.width * imageInfo.height * 3;
    return imageInfo;
}

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
    Convolution con;
    int a[] = { -1,0,1, -2, 0, 2, -1,0,1};
    Matrix<int> m(3,3,a);
    con.Convolute(&imageManager.ActualImage, m, renderImage);

}

TEST(Render, Scale) {
    FileFactory<ImageFileLoader *> fileFactory;
    fileFactory.AddFactory("bmp", [](){ return BMPFileLoader::CreateInstance(); });

    BImageManager imageManager;
    imageManager.SetFileFactory(fileFactory);
    imageManager.LoadDirectory(L".");

    for (float ratio = 0.2; ratio < 1.0; ratio = ratio + 0.02) {
        ImageInfo imageInfo = GetNewImageInfo(&imageManager.ActualImage, ratio);
        Image * renderImage = new Image(0);
        renderImage->SetImageInfo(imageInfo);
        renderImage->AllocateMemmory();

        Scale scaler;
        scaler.ScaleRect(&imageManager.ActualImage, renderImage, ratio);
        delete renderImage;
    }

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
