#include <PerfTimer.h>

void PerfTimer::start()
{
    startTime = timeFunction();
}

void PerfTimer::stop()
{
    totalTime = timeFunction() - startTime;
    return totalTime;
}

PerfTimer::PerfTimer(bool _start = true, unsigned long (*_timeFunction) (void) = millis)
    : timeFunction(_timeFunction)
{
    if (_start)
        start();
}