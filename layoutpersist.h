#ifndef LAYOUTPERSIST_H
#define LAYOUTPERSIST_H

static const int PersistScreenWidth        = 1920;
static const int PersistScreenHeight       = 1080;

static const int DefaultScreenWidth        = 1920;
static const int DefaultScreenHeight       = 1080;

static const int MaxScreenWidth            = 3840;
static const int MaxScreenHeight           = 2160;

static const int PersistPolyfitWidth       = 720;
static const int PersistPolyfitHeight      = 480;

static const int PersistPolyfitTableRow    = 4;
static const int PersistPolyfitTableCol    = 8;
static const int PersistPolyfitTableSize   = 32;

class LayoutPersist
{
public:
    static LayoutPersist* getInstance();

    void    setScreenSize(int width, int height);

    int     getPolyfitLayoutWidth() const;
    int     getPolyfitLayoutHeight() const;
    int     getPolyfitTableRow() const;
    int     getPolyfitTableCol() const;
    int     getPolyfitTableSize() const;
private:
    LayoutPersist();
    int mScreenWidth;
    int mScreenHeight;
};

#endif // LAYOUTPERSIST_H
