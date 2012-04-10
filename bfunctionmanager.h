#ifndef BFUNCTIONMANAGER_H
#define BFUNCTIONMANAGER_H

#include <QObject>
#include <QMenu>
#include <QMenuBar>
#include <vector>
#include "functions/bfilter.h"

class BFilterManager : public QObject
{
    Q_OBJECT
public:
    explicit BFilterManager(QObject *parent = 0);
    ~BFilterManager();
    void RegisterFilter(BFilter *filter);
    void RegisterToMenuBar(QMenuBar * menuBar);
signals:
    
public slots:
    void CallFilter(int filterId);
private:
    std::vector<BFilter *> filters;
    QMenu * filterMenu;
    
};

#endif // BFUNCTIONMANAGER_H
