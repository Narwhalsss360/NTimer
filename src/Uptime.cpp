#include <Arduino.h>
#include "TimeTypes.h"

static bool overflowed = false;
static time_t previousTime = 0;

time_t uptime()
{
    if (previousTime > millis())
        overflowed = true;
    return millis() + (overflowed ? 0 : __UINT32_MAX__);
}