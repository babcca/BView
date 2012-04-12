#ifndef BFILTER_H
#define BFILTER_H
#include <QObject>
#include "bimageprocess.h"
#include "bimagemanager.h"

class BFilter : public QObject
{
    Q_OBJECT

public:
    explicit BFilter(QObject *parent = 0)
        : QObject(parent) {
        SetChecked(false);
        SetMenuName(L"Other");
        SetMenuItemName(L"Unknown");
    }
    virtual void Execute(std::shared_ptr<Image> image, QObject * parent = 0) = 0;
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
        if (!IsChecked()) {
            Release();
        } else {
            Initialize();
        }
    }

protected:
    void SetMenuName(const std::wstring & menuName) {
        this->menuName = menuName;
    }
    void SetMenuItemName(const std::wstring & menuItemName) {
        this->menuItemName = menuItemName;
    }
    virtual void Release() {}
    virtual void Initialize() {}

private:
    std::wstring menuName;
    std::wstring menuItemName;
    bool state;
};

#endif // BFILTER_H
