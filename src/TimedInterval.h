#ifndef TimedInterval_h
#define TimedInterval_h

#include "TimeTypes.h"

/// @brief Check if an interval has elapsed. Auto updates `lastInterval`.
/// @param lastInterval last time interval elapsed
/// @param interval interval
/// @return `bool` true if elapsed
bool intervalElapsed(time_t& lastInterval, const time_t& interval);

#endif