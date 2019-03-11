#include "layoutpersist.h"
#include <QDebug>

LayoutPersist* LayoutPersist::getInstance()
{
    static LayoutPersist sLayoutPersist;
    return &sLayoutPersist;
}

LayoutPersist::LayoutPersist()
{
    mScreenWidth    = DefaultScreenWidth;
    mScreenHeight   = DefaultScreenHeight;
}

void LayoutPersist::setScreenSize(int width, int height)
{
    if (width < 0                   ||
            width > MaxScreenWidth  ||
            height < 0              ||
            height > MaxScreenHeight)
    {
        qDebug("invalid Screen Size: %dx%d", width, height);
    }

    mScreenWidth    = width;
    mScreenHeight   = height;
    qDebug("setScreenSize: %dx%d", width, height);
}

int LayoutPersist::getPolyfitLayoutWidth() const
{
    double ratio = mScreenWidth / static_cast<double>(PersistScreenWidth);
    return static_cast<int>(PersistPolyfitWidth * ratio);
}

int LayoutPersist::getPolyfitLayoutHeight() const
{
    double ratio = mScreenHeight / static_cast<double>(PersistScreenHeight);
    return static_cast<int>(PersistPolyfitHeight * ratio);
}

int LayoutPersist::getPolyfitTableCol() const
{
    return PersistPolyfitTableCol;
}

int LayoutPersist::getPolyfitTableRow() const
{
    return PersistPolyfitTableRow;
}

int LayoutPersist::getPolyfitTableSize() const
{
    return PersistPolyfitTableSize;
}
