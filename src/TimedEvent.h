#ifndef TimedEvent_h
#define TimedEvent_h

#include "TimeTypes.h"
#include <Callables.h>
#include <NEvents.h>

class TimedEvent;

struct ElapsedEventArgs
{
    TimedEvent* sender;
    ntime_t startTime;
    ntime_t elapsedTime;
    bool enabled;
};

class TimedEvent
{
public:
    /// @brief Class for timing events.
    /// @param interval interval
    /// @param autoReset re-enable timer after it has elapsed.
    TimedEvent(ntime_t interval = 0, bool autoReset = false);

    /// @brief Check if timer is running.
    /// @return `bool` true if running
    bool enabled();

    /// @brief Start the timer.
    void start();

    /// @brief Stop the timer.
    void stop();

    /// @brief Checks if the timer should have elapsed. invokes `elapsed` event.
    /// @return `bool` true if elapsed
    bool checkElapsed();

    /// @brief Check if the timer was successfully bound to the loop.
    /// @return `true` if bound
    bool bound();

    /// @brief Event invoked when timer elapsed.
    Event<TimedEvent, ElapsedEventArgs&> elapsed;

    /// @brief Re-enables timer after elapsed if set to `true`.
    bool autoReset;

    /// @brief interval of timer.
    ntime_t interval;

    ~TimedEvent();

private:

    ElapsedEventArgs elapsedArgs;
    ntime_t startAt;
};

void checkTimedEvents();

extern const bool checkTimedEvents_Bound;

#endif
