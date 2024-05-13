#include "TimeTypes.h"
#include <Arduino.h>

#define time_sym micros

ntime_t::half_int_type time_sym(void);

ntime_t uptime()
{
    static ntime_t::half_int_type overflow = 0;
    static ntime_t::half_int_type previousMeasure = 0;

    if (previousMeasure > time_sym())
        overflow++;
    previousMeasure = time_sym();

    return (ntime_t::int_type)previousMeasure + UINT32_MAX * overflow;
}
