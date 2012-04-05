#ifndef BDIRECTORY_H
#define BDIRECTORY_H
#include <string>
#include "QDir"
#include "QList"
#include <iostream>

struct BDirectory
{
    typedef QFileInfoList::const_iterator file_iterator;
    QDir::SortFlags SORT_FLAGS;
    QDir::Filters FILTER_FLAGS;
    BDirectory();
    ~BDirectory();
    void SetPath(std::wstring path);
    file_iterator file_begin() const;
    file_iterator file_end() const;
private:
    void LoadFileInfos();
    QDir directory;
    QFileInfoList fileInfosList;
};

#endif // BDIRECTORY_H
