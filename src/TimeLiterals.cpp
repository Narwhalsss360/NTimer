#include "TimeLiterals.h"

unsigned long operator"" _hz(unsigned long long hertz)
{
    return hertz / 1000;
}

unsigned long operator"" _s(unsigned long long seconds)
{
    return seconds * 1000;
}

unsigned long operator"" _m(unsigned long long minutes)
{
    return minutes * 60000;
}