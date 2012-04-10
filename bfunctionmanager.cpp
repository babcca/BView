#include "bfunctionmanager.h"

BFilterManager::BFilterManager(QObject *parent) :
    QObject(parent)
{
    filterMenu = new QMenu(tr("Filters"));
}

BFilterManager::~BFilterManager() {
    for (auto filter = filters.begin(); filter != filters.end(); ++filter) {
        delete *filter;
    }
}

void BFilterManager::RegisterFilter(BFilter *filter) {
    int filterId = filters.size();
    filters.push_back(filter);
    filterMenu->addAction(QString::fromStdWString(filter->GetMenuName()), this, SLOT(CallFilter(filterId)));
    //connect(filterMenu, SIGNAL(triggered(), this, SLOT(CallFilter(filterId))));

}

void BFilterManager::RegisterToMenuBar(QMenuBar *menuBar) {
    menuBar->addMenu(filterMenu);
}

void BFilterManager::CallFilter(int filterId) {
    BFilter * filter = filters[filterId];
    qDebug("ahoj svete %d", filterId);
}
