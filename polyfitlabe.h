#ifndef POLYFITLABE_H
#define POLYFITLABE_H

#include <QLabel>
class polyfitlabe : public QLabel
{
public:

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);

private:

};

#endif // POLYFITLABE_H
