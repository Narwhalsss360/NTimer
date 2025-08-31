#include "TimedEvent.h"
#include <stdcol.h>
#include "Uptime.h"
#if __has_include(<SketchBoundLibrary.h>)
#include <SketchBoundLibrary.h>
#define TimedEvent_Bindable
#endif


constexpr const int MAX_ACTIVE = 8;

TimedEvent* active[MAX_ACTIVE] = { nullptr };

void checkTimedEvents()
{
    for (TimedEvent*& timer : active)
        timer->checkElapsed();
}

#ifdef TimedEvent_Bindable
Function<void> checkTimedEventsInvokable = Function<void>(checkTimedEvents);
const bool checkTimedEvents_Bound = addSketchBinding(bind_loop, &checkTimedEventsInvokable);
#else
const bool checkTimedEvents_Bound = false;
#endif

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

    int i;
    for (i = 0; i < MAX_ACTIVE; i++) {
        if (active[i] == nullptr) {
            break;
        }
    }
    if (i == MAX_ACTIVE) {
        return;
    }
    active[i] = this;

    elapsedArgs.enabled = true;
    startAt = uptime();
}

void TimedEvent::stop()
{
    if (!enabled())
        return;

    int i;
    for (i = 0; i < MAX_ACTIVE; i++) {
        if (active[i] == this) {
            break;
        }
    }
    if (i == MAX_ACTIVE) {
        return;
    }
    active[i] = nullptr;
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
