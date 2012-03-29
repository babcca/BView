#ifndef BDIRECTORY_H
#define BDIRECTORY_H
#include <string>
#include "QDir"
#include "QList"
#include <iostream>

struct BDirectory
{
    typedef QStringList::const_iterator name_iterator;
    typedef QFileInfoList::const_iterator file_iterator;
    QDir::SortFlags SORT_FLAGS;
    QDir::Filters FILTER_FLAGS;
    BDirectory();
    ~BDirectory();
    void SetPath(std::wstring path);
    void LoadFileNames();
    void LoadFileInfos();
    const unsigned int GetRevision() const;
    name_iterator name_begin() const;
    name_iterator name_end() const;
    file_iterator file_begin() const;
    file_iterator file_end() const;
private:
    QDir * directory;
    QStringList fileNamesList;
    QFileInfoList fileInfosList;
    unsigned int revision;
};

#endif // BDIRECTORY_H
