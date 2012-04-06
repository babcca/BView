#include "bimagemanager.h"
/*
BImageManager::BImageManager(std::shared_ptr<FileFactory<ImageFileLoader *> > fileFactory) {
    SetFileFactory(fileFactory);
}
*/
BImageManager::BImageManager() : revision(0), ActualImage(*this) {
}

BImageManager::~BImageManager() {
    std::for_each(imagesId.begin(), imagesId.end(), [this](IMAGE_ID id) {
        BImageManager::imageCache::Instance()->DestroyRecord(id);
    });
}

void BImageManager::SetFileFactory(FileFactory<ImageFileLoader *> fileFactory) {
    this->fileFactory = fileFactory;
}

void BImageManager::LoadDirectory(const std::wstring & dirName) {
    BDirectory directory;
    directory.SetPath(dirName);
    IMAGE_ID oldImageId = ActualImage.GetActualId();
    for(auto i = directory.file_begin(); i != directory.file_end(); ++i) {
        const std::string suffix = GetSuffix(*i);
        bool fileLoaderExists = fileFactory.IsRegistred(suffix);
        if (fileLoaderExists) {
            QFileInfo fileInfo = *i;
            IMAGE_ID image_id = LoadImage(fileInfo);
        }
    }
    auto foundItem = std::find(imagesId.begin(), imagesId.end(), oldImageId);
    if (foundItem == imagesId.end()) {
        ActualImage.SetItem(imagesId.begin());
    } else {
        ActualImage.SetItem(foundItem);
    }

}

BImageManager::IMAGE_ID BImageManager::LoadImage(QFileInfo & fileInfo) {
    const std::string suffix = GetSuffix(fileInfo);
    FileFactory<ImageFileLoader *>::Loader fileLoader = fileFactory.GetLoader(suffix);
    if (fileLoader != 0) {
        fileLoader->SetFileInfo(fileInfo);
        // O vymazani se stara cache
        Image * image = new Image(fileLoader);
        IMAGE_ID image_id = imageCache::Instance()->InsertIntoCache(image);
        imagesId.push_back(image_id);
        ++revision;
        return image_id;
    } else {
        throw new std::exception();
    }
}

const std::string BImageManager::GetSuffix(const QFileInfo & fileInfo) const {
    std::string suffix = fileInfo.suffix().toLower().toStdString();
    return suffix;
}
