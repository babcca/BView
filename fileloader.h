#ifndef FILELOADER_H
#define FILELOADER_H
#include "QFileInfo"
#include "icacheitem.h"
#include "DataAllocator.h"
#include <iostream>
#include <fstream>


class FileLoader : public ICacheItem {
public:
    FileLoader() {
        IsCached(false);
    }
    virtual ~FileLoader() {
        DeleteFromCache();
    }

    void SetFileInfo(const QFileInfo & fileInfo) {
        this->fileInfo = fileInfo;
    }

    const std::wstring GetFullPath() const { return fileInfo.absoluteFilePath().toStdWString(); }

    virtual void LoadIntoCache() {
        if (!IsCached()) {
            std::ifstream file(GetFullPath(), std::ios::in | std::ios::binary);
            if (!file.is_open()) {
                throw new std::invalid_argument("Nemohu otevrit soubor");
            }
            int fileSize = GetFileSize(file);
            FileData.AllocateDataMemory(fileSize);
            std::shared_ptr<char> dataBuffer = FileData.GetAllocatedMemory();
            file.read(dataBuffer.get(), fileSize);
            file.close();
            IsCached(true);
        }
    }

    virtual void DeleteFromCache() {
        std::cout << "FileDelete" << std::endl;
        FileData.FreeAllocatedMemory();
    }


    virtual void UnloadFromCache() {
        std::cout << "FileDelete" << std::endl;
        FileData.FreeAllocatedMemory();
        IsCached(false);
    }
    DataAllocator FileData;
private:
    int GetFileSize(std::ifstream & ifstream_) {
        ifstream_.seekg(0, std::ios::end);
        std::streamoff size = ifstream_.tellg();
        ifstream_.seekg(0);
        return static_cast<int>(size);
    }

    QFileInfo fileInfo;
};


#endif // FILELOADER_H
