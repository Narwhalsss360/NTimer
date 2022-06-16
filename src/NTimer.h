#ifndef NTimer_h
#define NTimer_h

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <NDefs.h>
#include "NTimerMacros.h"
#include "NTimerEvents.h"
#include "TimeLiterals.h"

uint32_t UC_UPTIME_NAME;

inline bool interval(uint32_t& last, uint32_t interval)
{
    if (UC_UPTIME_NAME - last >= interval)
    {
        last = UC_UPTIME_NAME;
        return true;
    }
    return false;
}

typedef class NTimer;
#if (MAX_INSTANCES == 1)
NTimer *NTimerInstance = NULL;
#else
uint8_t NTimerInstanceCount = ZERO;
NTimer *NTimerInstances[MAX_INSTANCES] = { NULL };
#endif

void NTimerDelayLibInclude()
{
    LIB_LOOP_INCLUDE
}

class NTimer
{
private:
    uint8_t eventCount;
    NTimerEvent *events;
    uint8_t search(uint8_t id)
    {
        for (uint8_t eventIndex = ZERO; eventIndex < eventCount; eventIndex++)
        {
            if (events[eventIndex].id == id) return eventIndex;
        }
        return eventCount;
    }

public:
    NTimer()
        : eventCount(ZERO), events(NULL)
    {
#if (MAX_INSTANCES == 1)
        NTimerInstance = this;
#else
        if (NTimerInstanceCount == MAX_INSTANCES) return;
        NTimerInstances[NTimerInstanceCount] = this;
        NTimerInstanceCount++;
#endif
    }

    void addEvent(NTimerEvent newNTimerEvent)
    {
        uint8_t eventIndex = search(newNTimerEvent.id);
        if (eventIndex < eventCount)
        {
            changeEvent(newNTimerEvent);
            return;
        }
        if (eventCount < MAX_NTIMEREVENTS)
        {
            NTimerEvent* temp = new NTimerEvent[eventCount];
            memmove(temp, events, sizeof(NTimerEvent) * eventCount);

            events = new NTimerEvent[eventCount + 1];
            memmove(events, temp, sizeof(NTimerEvent) * eventCount + 1);
            delete[] temp;

            events[eventCount] = newNTimerEvent;
            eventCount++;
        }
    }

    void changeEvent(NTimerEvent newNTimerEventSettings)
    {
        uint8_t eventIndex = search(newNTimerEventSettings.id);
        if (eventIndex < eventCount)
        {
            events[eventIndex] = newNTimerEventSettings;
        }
    }

    void removeEvent(uint8_t id)
    {
        uint8_t eventIndex = search(id);
        if (eventIndex < eventCount)
        {
            NTimerEvent* temp = new NTimerEvent[eventCount];
            memmove(temp, events, sizeof(NTimerEvent) * eventCount);
            delete[] events;
            events = new NTimerEvent[eventCount - 1];

            memmove(events, temp, (eventIndex + 1) * sizeof(NTimerEvent));
            memmove((events + eventIndex), (temp + (eventIndex + 1)), ((eventCount - eventIndex) * sizeof(NTimerEvent)));

            delete[] temp;
            eventCount--;
        }
    }

    void removeEvent(NTimerEvent eventToDelete)
    {
        removeEvent(eventToDelete.id);
    }

    void start(uint8_t id = BYTE_MAX, uint8_t call = ZERO)
    {
        if (id == BYTE_MAX)
        {
            for (uint8_t eventIndex = ZERO; eventIndex < eventCount; eventIndex++)
            {
                events[eventIndex].enable = true;
                events[eventIndex].lastCallback = UC_UPTIME_NAME;
                if (call == CALL)
                {
                    events[eventIndex].callback({ UC_UPTIME_NAME, &events[eventIndex] });
                    events[eventIndex].iterations++;
                }
            }
            return;
        }

        uint8_t eventIndex = search(id);

        if (eventIndex < eventCount)
        {
            events[eventIndex].enable = true;
            events[eventIndex].lastCallback = UC_UPTIME_NAME;
            if (call == CALL)
            {
                events[eventIndex].callback({ UC_UPTIME_NAME, &events[eventIndex] });
                events[eventIndex].iterations++;
            }
        }
    }

    void start(NTimerEvent &eventToStart, uint8_t call = ZERO)
    {
        start(eventToStart.id, call);
    }

    void stop(uint8_t id = BYTE_MAX, bool resetIterations = true)
    {
        if (id == BYTE_MAX)
        {
            for (uint8_t eventIndex = ZERO; eventIndex < eventCount; eventIndex++)
            {
                events[eventIndex].enable = false;
                if (resetIterations) events[eventIndex].iterations = ZERO;
            }
            return;
        }

        uint8_t eventIndex = search(id);

        if (eventIndex < eventCount)
        {
            events[eventIndex].enable = false;
            if (resetIterations) events[eventIndex].iterations = ZERO;
        }
    }

    void stop(NTimerEvent& eventToStop, bool resetIterations = true)
    {
        stop(eventToStop.id, resetIterations);
    }

    void call(uint8_t id, uint8_t force = ZERO)
    {
        uint8_t eventIndex = search(id);
        if (eventIndex < eventCount)
        {
            events[eventIndex].callback(ElapsedEvent({ UC_UPTIME_NAME, &events[eventIndex] }));

            if (force == FORCE_CALL) return;

            events[eventIndex].iterations++;
            if (events[eventIndex].enable)
                events[eventIndex].lastCallback = UC_UPTIME_NAME;
        }
    }

    void call(NTimerEvent& eventToCall, uint8_t force = ZERO)
    {
        call(eventToCall.id, force);
    }

    void delay(uint32_t ms, uint16_t callerID = BYTE_MAX, void (*include)(void) = NULL)
    {
        if (callerID == BYTE_MAX)
        {
            delay(ms);
            return;
        }

        uint32_t startTime = UC_UPTIME_NAME;

        while (UC_UPTIME_NAME - startTime < ms)
        {
            for (uint8_t eventIndex = ZERO; eventIndex < eventCount; eventIndex++)
            {
                UC_UPTIME_NAME = millis();
                if (callerID == events[eventIndex].id) continue;

                if (events[eventIndex].enable)
                {
                    if (interval(events[eventIndex].lastCallback, events[eventIndex].time))
                    {
                        events[eventIndex].callback({ UC_UPTIME_NAME, &events[eventIndex] });
                        events[eventIndex].iterations++;

                        switch (events[eventIndex].mode)
                        {
                        case ONCE:
                            events[eventIndex].enable = false;
                            events[eventIndex].iterations = ZERO;
                            break;
                        case ITERATION_COUNT:
                            if (events[eventIndex].iterations == events[eventIndex].maxIterations)
                            {
                                events[eventIndex].enable = false;
                                events[eventIndex].iterations = ZERO;
                            }
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
            NTimerDelayLibInclude();
            if (include != NULL) include();
        }
    }

    void delay(uint32_t ms, NTimerEvent caller, void (*include)(void) = NULL)
    {
        this->delay(ms, caller.id, include);
    }

    void update()
    {
        if (eventCount == ZERO) return;

        for (uint8_t eventIndex = ZERO; eventIndex < eventCount; eventIndex++)
        {
            if (events[eventIndex].enable)
            {
                if (interval(events[eventIndex].lastCallback, events[eventIndex].time))
                {
                    events[eventIndex].callback({ UC_UPTIME_NAME, &events[eventIndex] });
                    events[eventIndex].iterations++;

                    switch (events[eventIndex].mode)
                    {
                    case ONCE:
                        events[eventIndex].enable = false;
                        events[eventIndex].iterations = ZERO;
                        break;
                    case ITERATION_COUNT:
                        if (events[eventIndex].iterations == events[eventIndex].maxIterations)
                        {
                            events[eventIndex].enable = false;
                            events[eventIndex].iterations = ZERO;
                        }
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    }

    NTimerEvent* getEventSettings(uint8_t id)
    {
        uint8_t eventIndex = search(id);
        if (eventIndex < eventCount) return &events[eventIndex];
        return NULL;
    }

    void operator+=(NTimerEvent newNTimerEvent)
    {
        addEvent(newNTimerEvent);
    }

    void operator-=(uint8_t id)
    {
        removeEvent(id);
    }

    void operator-=(NTimerEvent eventToDelete)
    {
        removeEvent(eventToDelete);
    }

    NTimerEvent* operator<<(uint8_t id)
    {
        return getEventSettings(id);
    }

    ~NTimer()
    {
#if (MAX_INSTANCES == 1)
        NTimerInstance = NULL;
#else
        delete[] events;
        for (uint8_t NTimerInstance = ZERO; NTimerInstance < NTimerInstanceCount; NTimerInstance++)
        {
            if (NTimerInstances[NTimerInstance] == this) NTimerInstances[NTimerInstance] = NULL;
            NTimerInstanceCount--;
        }
#endif
    }
};

extern void NTimer_h_userLoop();

void runtimeUpdate()
{
    UC_UPTIME_NAME = millis();
}

void NTimer_h_loop()
{
    runtimeUpdate();
#if (MAX_INSTANCES == 1)
    if (NTimerInstance != NULL) NTimerInstance->update();
#else
    for (uint8_t NTimerInstance = ZERO; NTimerInstance < NTimerInstanceCount; NTimerInstance++)
    {
        if (NTimerInstances[NTimerInstance] != NULL)
        {
            NTimerInstances[NTimerInstance]->update();
        }
    }
#endif
}

void loop()
{
    NTimer_h_loop();
    NTimer_h_userLoop();
}

#define loop NTimer_h_userLoop

#endif