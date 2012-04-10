#ifndef BFUNCTIONMANAGER_H
#define BFUNCTIONMANAGER_H

#include <QObject>
#include <QMenu>
#include <QMenuBar>
#include <vector>
#include <map>

#include "functions/grayscale.h"
#include "functions/edgedetect.h"

class BFilterManager : public QObject
{
    Q_OBJECT
public:
    explicit BFilterManager(QObject *parent = 0);
    ~BFilterManager();
    void RegisterFilter(BFilter *filter);
    void RegisterToMenuBar(QMenuBar * menuBar);
    QMenu * GetMenu(std::wstring &menuName);
    std::vector<BFilter *>::iterator begin();
    std::vector<BFilter *>::iterator end();
    
private:
    std::vector<BFilter *> filters;
    std::map<std::wstring, QMenu *> filterMenu;
    
};

#endif // BFUNCTIONMANAGER_H
