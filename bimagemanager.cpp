#include "bimagemanager.h"
#include "QDir"
#include <vector>

/*
BImageManager::BImageManager()
{
    QString path = QDir::current().path();
    QDir * directory = new QDir();
    directory->setFilter(QDir::Files);
    directory->setSorting(QDir::Name | QDir::LocaleAware);
    directory->setPath(path);
}

void SetDirectory(std::string path) {
    if (QDir::exists(path)) {
        directory->setPath(path);
    } else {
        throw new std::exception();
    }
}


void MoveNext() {
    actual_id + 1 == image_ids.size() ? 0 : ++actual_id;
}

void MovePrevious() {
    actual_id - 1 == 0 ? images_ids.size() - 1 : --actual_id;
}


images_file = dir.filter_image(["bmp", "jpg"]);
foreach (image_file in images_file) {
    int image_id = cahce.insert(image_file);
    image_ids.push_back(image_id);
}

int actual_id = image_ids[0];

BImage image = cache.getImage(actual_id);
glDraw(image);
*/


