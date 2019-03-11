#include "polyfitalgo.h"
#include <QtMath>
#define MAX_DEPTH  8
typedef struct
{
    int     depth;
    double  peak;
    double  coff[MAX_DEPTH];
} polyfitdata_t;

static polyfitdata_t s_front = {5, 0.43, -6.1221456, 12.2442667, -9.3446108, 3.2224832, 0.0012819};
QImage PolyfitProcess(QImage input, POLYFIT_TYPE type)
{
    polyfitdata_t *data = nullptr;
    switch (type)
    {
    case POLYFIT_TYPE::FRONT:
        data = &s_front;
        break;
    default:
        //TODO
        break;
    }
    if (nullptr == data)
    {
        return input;
    }

    int width   = input.width();
    int height  = input.height();
    int height1 = static_cast<int>((data->peak+1.f) * height);

    qDebug("dump data:");
    qDebug("            depth: %d", data->depth);
    qDebug("            peak: %lf", data->peak);
    for (int i = 0; i < data->depth; ++i)
    {
        qDebug("            coff%d: %lf", i, data->coff[i]);
    }
    qDebug("            ");
    qDebug("original image size: %d x %d", width, height);
    qDebug("new image size: %d x %d", width, height1);
    QImage newImage(width, height1, QImage::Format_RGB888);
    for (int w = 0; w < width; ++w)
    {
        double x    = w / static_cast<double>(width);
        double y    = 0.0;
        if (data->depth == 5)
        {
            y = data->coff[0] * qPow(x, 4) +
                    data->coff[1] * qPow(x, 3) +
                    data->coff[2] * qPow(x, 2) +
                    data->coff[3] * qPow(x, 1) +
                    data->coff[4] * qPow(x, 0);
        }

        int hbase   = static_cast<int>(y * height);
        if (w > 500 && w < 600) qDebug("x = %lf, y = %lf, hBase = %d", x, y, hbase);
        if (hbase < 0) hbase = 0;

        for (int h = 0 ; h < height; ++h)
        {
            newImage.setPixel(w, h+hbase, input.pixel(w, h));
        }
    }
    return newImage;
}
//void PolyfitAlgo::Process(polyfitdata_t *data)
//{

//}
