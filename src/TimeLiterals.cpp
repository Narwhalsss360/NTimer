#include "TimeLiterals.h"

unsigned long operator"" hz(unsigned long long hertz)
{
    return hertz / 1000;
}

unsigned long operator"" s(unsigned long long seconds)
{
    return seconds * 1000;
}

unsigned long operator"" m(unsigned long long minutes)
{
    return minutes * 60000;
}