#ifndef TimeLiterals_h
#define TimeLiterals_h

#include "TimeTypes.h"

static constexpr time_t::int_type operator"" hz(const time_t::int_type hertz)
{
    return time_t::cycles_per_second / hertz;
}

static constexpr time_t::int_type operator"" hz(const long double hertz)
{
    return time_t::cycles_per_second / hertz;
}

static constexpr time_t::int_type operator"" ms(const time_t::int_type milliseconds)
{
    return milliseconds * time_t::cycles_per_second / 1000;
}

static constexpr time_t::int_type operator"" ms(const long double milliseconds)
{
    return milliseconds * time_t::cycles_per_second / 1000;
}

static constexpr time_t::int_type operator"" s(time_t::int_type seconds)
{
    return seconds * time_t::cycles_per_second;
}

static constexpr time_t::int_type operator"" s(const long double seconds)
{
    return seconds * time_t::cycles_per_second;
}

static constexpr time_t::int_type operator"" m(time_t::int_type minutes)
{
    return minutes * time_t::cycles_per_second * 60;
}

static constexpr time_t::int_type operator"" m(const long double minutes)
{
    return minutes * time_t::cycles_per_second * 60;
}

static constexpr time_t::int_type operator"" h(time_t::int_type hours)
{
    return hours * time_t::cycles_per_second * 60 * 60;
}

static constexpr time_t::int_type operator"" h(const long double hours)
{
    return hours * time_t::cycles_per_second * 60 * 60;
}

static time_t operator"" t(const long double time)
{
    return time_t((time_t::int_type)time);
}

#endif