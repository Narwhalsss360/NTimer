#include "TimedEvent.h"
#include "SketchBoundLibrary.h"
#include "Uptime.h"

TimedEvent::TimedEvent(time_t interval, bool autoReset)
    : elapsed(Event<TimedEvent>()), autoReset(autoReset), elapsedArgs(ElapsedEventArgs()), interval(interval), startAt(0), checkElapsedRouterCallable(VoidMemberVoid<TimedEvent>(this, &TimedEvent::checkElapsedRouter))
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
    startAt = uptime();
    addSketchBinding(bind_loop, &checkElapsedRouterCallable);
    elapsedArgs.enabled = true;
}

void TimedEvent::stop()
{
    if (!enabled())
        return;
    removeSketchBinding(bind_loop, &checkElapsedRouterCallable);
    elapsedArgs.enabled = false;
}

bool TimedEvent::checkElapsed()
{
    if (enabled() && uptime() - startAt >= interval)
    {
        elapsedArgs.elapsedTime = uptime();
        elapsedArgs.startTime = startAt;
        startAt = uptime();
        elapsed(&elapsedArgs);

        if (!autoReset)
            stop();
        return true;
    }
    return false;
}

void TimedEvent::checkElapsedRouter()
{
    checkElapsed();
}

TimedEvent::~TimedEvent()
{
    stop();
}