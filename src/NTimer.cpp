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
    : eventsLength(NULL), events(NULL), runtime(millis())
{
}

NTimerClass::~NTimerClass()
{
    free(events);
}

bool NTimerClass::addEvent(evt newEvent)
{
    uint8_t index = search(newEvent.id);
    if (index < eventsLength)
    {
        changeEvent(newEvent);
        return false;
    }
    if (eventsLength)
    {
        pEvt temp = new evt[eventsLength];
        memcpy(temp, events, sizeof(evt) * eventsLength);
        eventsLength++;
        events = new evt[eventsLength];
        memcpy(events, temp, sizeof(evt) * eventsLength);
        events[eventsLength - 1] = newEvent;
        delete[] temp;
        return true;
    }
    eventsLength++;
    events = new evt[eventsLength];
    events[eventsLength - 1] = newEvent;
    return true;
}

bool NTimerClass::changeEvent(evt event)
{
    uint8_t index = search(event.id);
    if (index < eventsLength)
    {
        if (events[index].enable)
            event.enable = true;
        events[index] = event;
    }
    return false;
}

bool NTimerClass::removeEvent(uint8_t id)
{
    uint8_t index = search(id);
    if (index < eventsLength)
    {
        pEvt temp = new evt[eventsLength];
        memcpy(temp, events, sizeof(evt) * eventsLength);
        delete[] events;
        events = new evt[eventsLength - 1];

        memmove(events, temp, (index + 1)*sizeof(evt));
        memmove(events + index, temp + (index + 1), ((eventsLength - index)*sizeof(evt)));

        delete[] temp;
        eventsLength--;
        return true;
    }
    return false;
}

uint8_t NTimerClass::search(uint8_t id)
{
    for (uint8_t i = ZERO; i < eventsLength; i++)
    {
        if (events[i].id == id)
            return i;
    }
    return eventsLength;
}

void NTimerClass::update()
{
    runtime = millis();
    if (!eventsLength)
        return;
    for (uint8_t i = ZERO; i < eventsLength; i++)
    {
        if (events[i].enable)
        {
            if (interval(events[i].lastCallback, events[i].time))
            {
                events[i].callback({runtime, &events[i]});
                switch (events[i].mode)
                {
                case ONCE:
                    events[i].enable = false;
                    break;
                default:
                    break;
                }
            }
        }
    }
}

void NTimerClass::start()
{
    for (uint8_t i = ZERO; i < eventsLength; i++)
    {
        events[i].enable = true;
        events[i].lastCallback = runtime;
    }
}

void NTimerClass::stop()
{
    for (uint8_t i = ZERO; i < eventsLength; i++)
    {
        events[i].enable = false;
    }
}

bool NTimerClass::start(uint8_t id)
{
    uint8_t index = search(id);
    if (index < eventsLength)
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
    if (index < eventsLength)
    {
        events[index].enable = false;
        return true;
    }
    return false;
}

NTimerClass NTimer = NTimerClass();