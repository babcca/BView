#include "gtest/gtest.h"
#include <algorithm>
#include <iostream>
#include "bdirectory.h"
#include "bsingletoncache.h"
#include "bcache.h"
#include "fileloaderfactory.h"
#include "bmpfileloader.h"

    TEST(Directory, Listing) {
        BDirectory directory;
        directory.SetPath(L"c:/");
        directory.LoadFileNames();
        std::for_each(directory.name_begin(), directory.name_end(), [](QString filename) {
            std::cout << filename.toStdString() << std::endl;
        });

        directory.LoadFileInfos();
        std::for_each(directory.file_begin(), directory.file_end(), [](QFileInfo fileinfo) {
            std::cout << fileinfo.suffix().toStdString() << std::endl;
        });
    }
class cache_traits {
};
class Image : public ICacheItem {
public:
    Image(FileLoader * file_cache_id_) : file_cache(file_cache_id_) {
        IsCached(false);
    }
    void GetImage() {
        if (!IsCached()) {
            typedef BSingletonCache<BCache<FileLoader *, cache_traits> > fileCache;
            auto instance = fileCache::Instance();
            FileLoader * file = instance->GetRecord(2);
            std::wcout << file->GetFullPath() << std::endl;

            // decode from file
        }
    }
    virtual void LoadIntoCache() {
        std::cout << "ImageLoadIntoCache" << std::endl;
        //typedef BSingletonCache<BCache<FileLoader *, cache_traits> > fileCache;
        //auto instance = fileCache::Instance();
        //FileLoader * file = instance->GetRecord(file_cace_id);
        file_cache->LoadIntoCache();

    }
    virtual void DeleteFromCache() {
        std::cout << "ImageDelete" << std::endl;
        file_cache->DeleteFromCache();

    }
    virtual void UnloadFromCache() {
        std::cout << "ImageUnload" << std::endl;
        file_cache->UnloadFromCache();
    }

    FileLoader * file_cache;
};



class JPGFile : FileLoader {
public:
    static FileLoader * CreateInstance() {
        return new JPGFile();
    }
};
    TEST(Cache, LoadImage) {
        BDirectory directory;
        directory.SetPath(L".");
        directory.LoadFileInfos();
        auto fileCache = BSingletonCache<BCache<FileLoader *, cache_traits> >::Instance();
        auto imageCache = BSingletonCache<BCache<Image *, cache_traits> >::Instance();

        std::vector<unsigned int> images;
        FileFactory fileFactory;
        fileFactory.AddFactory("bmp", [](){ return BMPFileLoader::CreateInstance(); });
        fileFactory.AddFactory("jpg", [](){ return JPGFile::CreateInstance(); });

        std::for_each(directory.file_begin(), directory.file_end(), [fileCache, imageCache, &images, &fileFactory](QFileInfo fileInfo) {
                      FileLoader * fileObject = fileFactory[fileInfo.suffix().toLower().toStdString()];
        if (fileObject != 0) {
                      unsigned int fileId = fileCache->InsertIntoCache(fileObject);
                      unsigned int imageId = imageCache->InsertIntoCache(new Image(fileObject));
                      images.push_back(imageId);
        }
        });
        //imageCache->GetRecord(images[0]);
        EXPECT_EQ(2, images.size());
    }

        TEST(SingletonCache, OneInstance) {
            typedef BSingletonCache<BCache<FileLoader *, cache_traits> > fileCache;
            auto instance = fileCache::Instance();
            EXPECT_EQ(instance, fileCache::Instance());
        }

        TEST(SingletonCache, Persistence) {
            typedef BSingletonCache<BCache<Image *, cache_traits> > imageCache;
            auto instance = imageCache::Instance();

            FileFactory fileFactory;
            fileFactory.AddFactory("bmp", [](){ return BMPFileLoader::CreateInstance(); });

            BDirectory directory;
            directory.SetPath(L"c:/");
            directory.LoadFileInfos();
            std::for_each(directory.file_begin(), directory.file_end(), [instance, &fileFactory](QFileInfo fileInfo) {
                          FileLoader * fileObject = fileFactory[fileInfo.suffix().toLower().toStdString()];
            if (fileObject != 0) {
                          fileObject->SetFileInfo(fileInfo);
                          instance->InsertIntoCache(new Image(fileObject));

            }
            });
            Image * image = instance->GetRecord(2);
            //std::wcout << file->GetFullPath() << std::endl;
        }

void TestAll(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
}
