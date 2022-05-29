#include <PerfTimer.h>

void PerfTimer::start()
{
    if (running)
        return;
    running = true;
    startTime = timeFunction();
}

void PerfTimer::stop()
{
    if (!running)
        return;
    totalTime = timeFunction() - startTime;
}

PerfTimer::PerfTimer(bool _start = true, unsigned long (*_timeFunction) (void) = millis)
    :timeFunction(_timeFunction)
{
    if (_start)
        start();
}