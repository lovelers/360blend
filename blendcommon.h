#ifndef BLENDCOMMON_H
#define BLENDCOMMON_H

#define POLYFIT_X_COUNT (32)
#define POLYFIT_MAX_COUNT (5)

typedef enum
{
    BLEND_START = 0,
    FRONT_BLEND = BLEND_START,
    BACK_BLEND,
    LEFT_BLEND,
    RIGHT_BLEND,
    BLEND_END
} BLEND_TYPE;

typedef struct polyfitdata
{
    double xData[POLYFIT_X_COUNT];
    double yData[POLYFIT_X_COUNT];
    double polyVal[POLYFIT_MAX_COUNT];
} polyfitdata_t;

#endif // BLENDCOMMON_H
