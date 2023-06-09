#ifndef TimeLiterals_h
#define TimeLiterals_h

#include "TimeTypes.h"

constexpr time_t operator"" hz(time_t hertz)
{
    return 1000 / hertz;
}

constexpr time_t operator"" hz(const long double hertz)
{
    return 1000 / hertz;
}

constexpr time_t operator"" s(time_t seconds)
{
    return seconds * 1000;
}

constexpr time_t operator"" s(const long double seconds)
{
    return seconds * 1000;
}

constexpr time_t operator"" m(time_t minutes)
{
    return minutes * 1000 * 60;
}

constexpr time_t operator"" m(const long double minutes)
{
    return minutes * 1000 * 60;
}

constexpr time_t operator"" h(time_t hours)
{
    return hours * 1000 * 60 * 60;
}

constexpr time_t operator"" h(const long double hours)
{
    return hours * 1000 * 60 * 60;
}

constexpr time_t operator"" t(const long double time)
{
    return (time_t)time;
}
#endif