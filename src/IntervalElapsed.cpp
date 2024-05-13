#include "TimedInterval.h"
#include "Uptime.h"

bool intervalElapsed(ntime_t& lastInterval, const ntime_t& interval)
{
    if (uptime() - lastInterval >= interval)
    {
        lastInterval = uptime();
        return true;
    }
    return false;
}
