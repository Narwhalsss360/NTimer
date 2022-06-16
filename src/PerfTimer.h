#ifndef PerfTimer_h
#define PerfTimer_h

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <NDefs.h>
#include "NTimerMacros.h"
#include "PerfTimer.h"

#ifdef NTimer_h
#define time UC_UPTIME_NAME
#else
#define time millis()
#endif

struct PerfTimer
{
private:
    unsigned long (*timeFunction) (void);
public:
    uint32_t startTime = ZERO;
    uint32_t totalTime = ZERO;

    PerfTimer(bool startState = true, unsigned long (*_timeFunction) (void) = millis)
        : timeFunction(_timeFunction), startTime(time), totalTime(ZERO)
    {
        if (startState) start();
    }

    void start()
    {
        startTime = time;
    }

    uint32_t stop()
    {
        totalTime = timeFunction() - startTime;
        return totalTime;
    }
};

typedef PerfTimer PT;

#undef time

#endif