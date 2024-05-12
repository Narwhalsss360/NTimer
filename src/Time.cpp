#include "TimeTypes.h"
#include <Print.h>
#include <math.h>

ntime_t::ntime_t()
    : time(0)
{
}

ntime_t::ntime_t(const int_type& time)
    : time(time)
{
}

ntime_t::int_type ntime_t::milliseconds() const
{
    return (time * 1000) / cycles_per_second; //Can't pre-process (1000 / cycles_per_second), results in decimal
}

ntime_t::int_type& ntime_t::operator=(const int_type& time)
{
    this->time = time;
    return this->time;
}

ntime_t& ntime_t::operator=(const ntime_t& other)
{
    time = other.time;
    return *this;
}

ntime_t::operator ntime_t::int_type&()
{
    return time;
}

ntime_t::operator const ntime_t::int_type&() const
{
    return time;
}

String ntime_t::toString() const
{
    int_type copy = time;
    int16_t length = log10(copy) + 1;
    char* str = new char[length + 1];
    str[length] = '\0';
    for (length -= 1; length >= 0; length--)
    {
        str[length] = '0' + (copy % 10);
        copy /= 10;
    }
    String result = String(str);
    delete[] str;
    return result;
}

size_t ntime_t::printTo(Print& print) const
{
    return print.print(toString());
}
