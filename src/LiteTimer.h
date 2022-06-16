#ifndef LiteTimer_h
#define LiteTimer_h

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <NDefs.h>
#include "NTimerMacros.h"
#include "TimeLiterals.h"

#ifndef NTimer_h
#define time millis()
bool interval(uint32_t &last, uint32_t period)
{
    if (millis() - last >= period)
    {
        last = millis();
        return true;
    }
    return false;
}
#else
#define time UC_UPTIME_NAME
#endif

#define START true

class LiteTimer
{
public:
    bool enabled;
    uint32_t lastTick;
    uint32_t tickInterval;

    LiteTimer(uint32_t newInterval = ZERO, bool startState = true)
        : enabled(startState), lastTick(time), tickInterval(newInterval)
    {

    }

    void start()
    {
        lastTick = time;
        enabled = true;
    }

    bool tick()
    {
        return interval(lastTick, tickInterval);
    }

    void stop()
    {
        enabled = false;
    }

    operator bool()
    {
        return tick();
    }

    ~LiteTimer()
    {
        
    }
};

#undef time

#endif