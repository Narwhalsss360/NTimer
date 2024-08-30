#include "TimedEvent.h"
#include <stdcol.h>
#include "Uptime.h"
#include <SketchBoundLibrary.h>

stdcol::dynamic_array<TimedEvent*> active;

void checkTimedEvents()
{
    for (TimedEvent*& timer : active)
    {
        timer->checkElapsed();
    }
}

bool TIMERS_BOUND = addSketchBinding(bind_loop, &invokable_get(checkTimedEvents));

TimedEvent::TimedEvent(ntime_t interval, bool autoReset)
    : elapsed(Event<TimedEvent, ElapsedEventArgs&>()), autoReset(autoReset), elapsedArgs(ElapsedEventArgs()), interval(interval), startAt(0)
{
}

bool TimedEvent::enabled()
{
    return elapsedArgs.enabled;
}

void TimedEvent::start()
{
    if (enabled())
        return;
    if (!active.insert(active.size(), this))
        return;

    elapsedArgs.enabled = true;
    startAt = uptime();
}

void TimedEvent::stop()
{
    if (!enabled())
        return;
    for (int i = 0; i < active.size(); i++)
        if (active[i] == this)
            active.remove(i);

    elapsedArgs.enabled = false;
}

bool TimedEvent::checkElapsed()
{
    elapsedArgs.elapsedTime = uptime();
    if (enabled() && elapsedArgs.elapsedTime - startAt >= interval)
    {
        elapsedArgs.startTime = startAt;
        startAt = elapsedArgs.elapsedTime;
        elapsed(elapsedArgs);

        if (!autoReset)
            stop();
        return true;
    }
    return false;
}

TimedEvent::~TimedEvent()
{
    stop();
}
