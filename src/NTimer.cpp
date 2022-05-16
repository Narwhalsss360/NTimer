#include "NTimer.h"

bool interval(uint32_t &lastRun, uint32_t interval)
{
    if (NTimer.runtime - lastRun >= interval)
    {
        lastRun = NTimer.runtime;
        return true;
    }
    else
    {
        return false;
    }
}

NTimerClass::NTimerClass()
    : timers(NULL), events(NULL), runtime(millis())
{
}

NTimerClass::~NTimerClass()
{
    free(events);
}

bool NTimerClass::newTimer(evt newEvent)
{
    uint8_t index = search(newEvent.id);
    if (index < timers)
    {
        changeTimer(newEvent);
        return false;
    }
    if (timers)
    {
        pEvt temp = new evt[timers];
        memcpy(temp, events, sizeof(evt) * timers);
        timers++;
        events = new evt[timers];
        memcpy(events, temp, sizeof(evt) * timers);
        events[timers - 1] = newEvent;
        delete[] temp;
        return true;
    }
    timers++;
    events = new evt[timers];
    events[timers - 1] = newEvent;
    return true;
}

bool NTimerClass::changeTimer(evt event)
{
    uint8_t index = search(event.id);
    if (index < timers)
    {
        if (events[index].enable)
            event.enable = true;
        events[index] = event;
    }
    return false;
}

bool NTimerClass::removeTimer(uint8_t id)
{
    uint8_t index = search(id);
    if (index < timers)
    {
        /* pEvt temp = new evt[timers];
        memcpy(temp, events, sizeof(evt) * timers);
        delete[] events;
        events = new evt[timers - 1];
        memcpy(events, temp, sizeof(evt) * index + 1);
        memcpy(events, temp + index + 1, (sizeof(evt) * (timers - index))); // <- TEST!
        delete[] temp;
        timers--; */
        return true;
    }
    return false;
}

uint8_t NTimerClass::search(uint8_t id)
{
    for (uint8_t i = ZERO; i < timers; i++)
    {
        if (events[i].id == id)
            return i;
    }
    return timers;
}

void NTimerClass::update()
{
    runtime = millis();
    for (uint8_t i = ZERO; i < timers; i++)
    {
        if (events[i].enable)
        {
            if (interval(events[i].lastCallback, events[i].time))
            {
                events[i].callback({events[i].id, runtime});
            }
        }
    }
}

void NTimerClass::start()
{
    for (uint8_t i = ZERO; i < timers; i++)
    {
        events[i].enable = true;
        events[i].lastCallback = runtime;
    }
}

void NTimerClass::stop()
{
    for (uint8_t i = ZERO; i < timers; i++)
    {
        events[i].enable = false;
    }
}

bool NTimerClass::start(uint8_t id)
{
    uint8_t index = search(id);
    if (index < timers)
    {
        events[index].enable = true;
        events[index].lastCallback = runtime;
        return true;
    }
    return false;
}

bool NTimerClass::stop(uint8_t id)
{
    uint8_t index = search(id);
    if (index < timers)
    {
        events[index].enable = false;
        return true;
    }
    return false;
}

NTimerClass NTimer = NTimerClass();