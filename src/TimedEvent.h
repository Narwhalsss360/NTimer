#ifndef TimedEvent_h
#define TimedEvent_h

#include "TimeTypes.h"
#include <Callables.h>
#include <NEvents.h>

class TimedEvent;

struct ElapsedEventArgs
{
    TimedEvent* sender;
    time_t startTime;
    time_t elapsedTime;
    bool enabled;
};


class TimedEvent
{
public:
    TimedEvent(time_t = 0, bool = false);

    bool enabled();

    void start();

    void stop();

    bool checkElapsed();

    bool bound();

    Event<TimedEvent> elapsed;

    bool autoReset;

    time_t interval;

    ~TimedEvent();
private:
    void checkElapsedRouter();

    ElapsedEventArgs elapsedArgs;
    time_t startAt;
    VoidMemberVoid<TimedEvent> checkElapsedRouterCallable;
};

#endif