#include "TimedInterval.h"
#include "Uptime.h"

bool intervalElapsed(time_t& lastInterval, const time_t& interval)
{
    if (uptime() - lastInterval >= interval)
    {
        lastInterval = uptime();
        return true;
    }
    return false;
}