#ifndef TimeLiterals_h
#define TimeLiterals_h

#include "TimeTypes.h"

static constexpr ntime_t::int_type operator"" _hz(const ntime_t::int_type hertz)
{
    return ntime_t::cycles_per_second / hertz;
}

static constexpr ntime_t::int_type operator"" _hz(const long double hertz)
{
    return ntime_t::cycles_per_second / hertz;
}

static constexpr ntime_t::int_type operator"" _ms(const ntime_t::int_type milliseconds)
{
    return milliseconds * ntime_t::cycles_per_second / 1000;
}

static constexpr ntime_t::int_type operator"" _ms(const long double milliseconds)
{
    return milliseconds * ntime_t::cycles_per_second / 1000;
}

static constexpr ntime_t::int_type operator"" _s(ntime_t::int_type seconds)
{
    return seconds * ntime_t::cycles_per_second;
}

static constexpr ntime_t::int_type operator"" _s(const long double seconds)
{
    return seconds * ntime_t::cycles_per_second;
}

static constexpr ntime_t::int_type operator"" _m(ntime_t::int_type minutes)
{
    return minutes * ntime_t::cycles_per_second * 60;
}

static constexpr ntime_t::int_type operator"" _m(const long double minutes)
{
    return minutes * ntime_t::cycles_per_second * 60;
}

static constexpr ntime_t::int_type operator"" _h(ntime_t::int_type hours)
{
    return hours * ntime_t::cycles_per_second * 60 * 60;
}

static constexpr ntime_t::int_type operator"" _h(const long double hours)
{
    return hours * ntime_t::cycles_per_second * 60 * 60;
}

static ntime_t operator"" _t(const long double time)
{
    return ntime_t((ntime_t::int_type)time);
}

#endif
