#ifndef TimeTypes_h
#define TimeTypes_h

#include <WString.h>
#include <Printable.h>

/// @brief type used by NTimer for time.
struct time_t : Printable
{
    using int_type = unsigned long long;

    using half_int_type = unsigned long;

    static constexpr int_type max_time = UINT64_MAX;

    static constexpr half_int_type cycles_per_second = 1000000;

    int_type time;

    time_t();

    time_t(const int_type& time);

    int_type milliseconds() const;

    int_type& operator=(const int_type& time);

    time_t& operator=(const time_t& other);

    operator int_type&();

    operator const int_type&() const;

    String toString() const;

    size_t printTo(Print& print) const;
};

#endif