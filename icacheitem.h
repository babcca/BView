#ifndef ICACHEITEM_H
#define ICACHEITEM_H

class ICacheItem {
public:
    virtual void LoadIntoCache() = 0;
    virtual void DeleteFromCache() = 0;
    const bool IsCached() const { return isCached; }
protected:
    void IsCached(bool isCached) { this->isCached = isCached; }
private:
    bool isCached;
};

#endif // ICACHEITEM_H
