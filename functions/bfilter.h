#ifndef BFILTER_H
#define BFILTER_H
#include <QObject>
#include "bimageprocess.h"

class BFilter : public QObject
{
    Q_OBJECT

public:
    explicit BFilter(QObject *parent = 0) : QObject(parent) {
        SetChecked(false);
        SetMenuName(L"Other");
        SetMenuItemName(L"Unknown");
    }
    virtual void Execute(Image * image, Image * out) = 0;

    std::wstring GetMenuName() const {
        return menuName;
    }
    std::wstring GetItemMenuName() const {
        return menuItemName;
    }

    const bool IsChecked() const {
        return state;
    }

signals:

public slots:
    void SetChecked(bool state) {
        this->state = state;
        qDebug("ahoj %d", state);
    }

protected:
    void SetMenuName(const std::wstring & menuName) {
        this->menuName = menuName;
    }
    void SetMenuItemName(const std::wstring & menuItemName) {
        this->menuItemName = menuName;
    }

private:
    std::wstring menuName;
    std::wstring menuItemName;
    bool state;
};

#endif // BFILTER_H
