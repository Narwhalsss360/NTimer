#include "TimeTypes.h"
#include <Arduino.h>

#define time_sym micros

time_t::half_int_type time_sym(void);

time_t uptime()
{
    static time_t::half_int_type overflow = 0;
    static time_t::half_int_type previousMeasure = 0;

    if (previousMeasure > time_sym())
        overflow++;
    previousMeasure = time_sym();

    return (time_t::int_type)previousMeasure + UINT32_MAX * overflow;
}