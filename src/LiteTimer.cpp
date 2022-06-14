#include "LiteTimer.h"

#ifdef NTimer_h
#define time runtime
#else
#define time millis()

bool interval(uint32_t &last, uint32_t interval)
{
    if (millis() - last >= interval)
    {
        last = millis();
        return true;
    }
    return false;
}
#endif

LiteTimer::LiteTimer(uint32_t newInterval = ZERO, bool startState = true)
    : enabled(startState), lastTick(time), tickInterval(newInterval)
{

}

void LiteTimer::start()
{
    lastTick = time;
    enabled = true;
}

void LiteTimer::stop()
{
    enabled = false;
}

void LiteTimer::operator bool()
{
    return interval(lastTick, tickInterval);
}