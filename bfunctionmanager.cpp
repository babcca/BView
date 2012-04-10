#include "bfunctionmanager.h"

BFilterManager::BFilterManager(QObject *parent) :
    QObject(parent)
{
}

BFilterManager::~BFilterManager() {
    for (auto filter = filters.begin(); filter != filters.end(); ++filter) {
        delete *filter;
    }
}

void BFilterManager::RegisterFilter(BFilter *filter) {
    QMenu * menu = GetMenu(filter->GetMenuName());
    QString menuItemName = QString::fromStdWString(filter->GetItemMenuName());
    QAction * menuItem = menu->addAction(menuItemName);
    menuItem->setCheckable(true);
    menuItem->setChecked(false);
    connect(menuItem, SIGNAL(toggled(bool)), filter, SLOT(SetChecked(bool)));
    filters.push_back(filter);
}

void BFilterManager::RegisterToMenuBar(QMenuBar *menuBar) {
    for (auto menu = filterMenu.begin(); menu != filterMenu.end(); ++menu) {
        menuBar->addMenu(menu->second);
    }
}

std::vector<BFilter *>::iterator BFilterManager::begin() {
    return filters.begin();
}

std::vector<BFilter *>::iterator BFilterManager::end() {
    return filters.end();
}

QMenu * BFilterManager::GetMenu(std::wstring & menuName) {
    auto menu = filterMenu.find(menuName);
    if (menu == filterMenu.end()) {
        QString menuNameQt = QString::fromStdWString(menuName);
        QMenu * newMenu = new QMenu(menuNameQt);
        filterMenu[menuName] = newMenu;
        return newMenu;
    } else {
        return menu->second;
    }
}
