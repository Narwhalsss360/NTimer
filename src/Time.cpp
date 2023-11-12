#include "TimeTypes.h"
#include <Print.h>
#include <math.h>

time_t::time_t()
    : time(0)
{
}

time_t::time_t(const int_type& time)
    : time(time)
{
}

time_t::int_type time_t::milliseconds() const
{
    return (time * 1000) / cycles_per_second; //Can't pre-process (1000 / cycles_per_second), results in decimal
}

time_t::int_type& time_t::operator=(const int_type& time)
{
    this->time = time;
    return this->time;
}

time_t& time_t::operator=(const time_t& other)
{
    time = other.time;
    return *this;
}

time_t::operator time_t::int_type&()
{
    return time;
}

time_t::operator const time_t::int_type&() const
{
    return time;
}

String time_t::toString() const
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

size_t time_t::printTo(Print& print) const
{
    return print.print(toString());
}