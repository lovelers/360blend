#include "polyfitlabel.h"
#include "polyfittablemodel.h"
#include "layoutpersist.h"

#include <QPainter>
PolyfitLabel::PolyfitLabel(QWidget *parent, Qt::WindowFlags f)
    :QLabel(parent, f)
{
    LayoutPersist *layout   = LayoutPersist::getInstance();
    mPointSize              = layout->getPolyfitTableSize();
    assert(mPointSize > 0);

    mpPointData = new float[mPointSize];
    for (int i = 0; i < mPointSize; i++)
    {
        mpPointData[i] = 1.f;
    }
}

PolyfitLabel::PolyfitLabel(const QString &text, QWidget *parent, Qt::WindowFlags f)
    :QLabel(text, parent, f)
{

}

void PolyfitLabel::updateData(float* data, int size)
{
    assert(size <= mPointSize && size > 0 && nullptr != data);

    for (int i = 0; i < size; i++)
    {
        if (data[i] > 1.f)
        {
            mpPointData[i] = 1.f;
        }
        else if (data[i] < 0)
        {
            mpPointData[i] = 0.f;
        }
        else
        {
            mpPointData[i] = data[i];
        }
    }
    this->update();
    //
}
void PolyfitLabel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen     pen;
    int left            = this->geometry().left();
    int top             = this->geometry().top();
    int width           = this->width();
    int height          = this->height();
    int paddingWidth    = static_cast<int>(width * 0.1);
    int paddingHeight   = static_cast<int>(height * 0.1);


    qDebug("label position: %d, %d, %d, %d",
           left, top, width, height);

    // here the diagram should square.
    int drawHeight      = (height - 2 * paddingHeight);
    int drawWidth       = drawHeight;

    int originX         = left;
    int originY         = drawHeight + top;

    // Draw the aix.
    pen.setColor(Qt::darkCyan);
    pen.setWidth(2);
    painter.setPen(pen);

    painter.drawLine(originX, originY, originX + drawWidth, originY);
    painter.drawLine(originX, originY, originX, originY - drawHeight);

    pen.setWidth(1);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    QPoint start, end;

    int unitWidth       = drawWidth / mPointSize;
    start.setX(0 * unitWidth + originX);
    start.setY(originY -  static_cast<int>(drawHeight * mpPointData[0]));
    for (int i = 1; i < mPointSize; i++)
    {
        end.setX(i * unitWidth + originX);
        end.setY(originY -  static_cast<int>(drawHeight * mpPointData[i]));
        painter.drawLine(start, end);
        start = end;
    }

    //QLabel::paintEvent(event);
}

PolyfitLabel::~PolyfitLabel()
{

}
