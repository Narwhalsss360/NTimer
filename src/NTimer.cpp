#define NTimer_cpp
#include "NTimer.h"

uint32_t runtime;
static NTimer *instance = ZERO;

inline bool interval(uint32_t &lastRun, uint32_t interval)
{
    if (runtime - lastRun >= interval)
    {
        lastRun = runtime;
        return true;
    }
    else
    {
        return false;
    }
}

NTimer::NTimer()
    : eventsLength(NULL), events(NULL)
{
    if (instance == NULL)
        instance = this;
}

NTimer::~NTimer()
{
    delete [] events;
    if (instance == this)
        instance = ZERO;
}

bool NTimer::addEvent(evt newEvent)
{
    uint8_t event = search(newEvent.id);
    if (event < eventsLength)
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

bool NTimer::changeEvent(evt newEvent)
{
    uint8_t event = search(newEvent.id);
    if (event < eventsLength)
    {
        if (events[event].enable)
            newEvent.enable = true;
        events[event] = newEvent;
    }
    return false;
}

bool NTimer::removeEvent(uint8_t id)
{
    uint8_t event = search(id);
    if (event < eventsLength)
    {
        pEvt temp = new evt[eventsLength];
        memcpy(temp, events, sizeof(evt) * eventsLength);
        delete[] events;
        events = new evt[eventsLength - 1];

        memmove(events, temp, (event + 1)*sizeof(evt));
        memmove(events + event, temp + (event + 1), ((eventsLength - event)*sizeof(evt)));

        delete[] temp;
        eventsLength--;
        return true;
    }
    return false;
}

uint8_t NTimer::search(uint8_t id)
{
    for (uint8_t event = ZERO; event < eventsLength; event++)
    {
        if (events[event].id == id)
            return event;
    }
    return eventsLength;
}

void NTimer::update()
{
    if (!eventsLength)
        return;
    for (uint8_t event = ZERO; event < eventsLength; event++)
    {
        if (events[event].enable)
        {
            if (interval(events[event].lastCallback, events[event].time))
            {
                events[event].callback({runtime, &events[event]});
                events[event].iterations++;
                switch (events[event].mode)
                {
                case ONCE:
                    events[event].enable = false;
                    events[event].iterations = ZERO;
                    break;
                case ITERATION_COUNT:
                    if (events[event].iterations == (events[event].maxIterations - 1))
                    {
                        events[event].enable = false;
                        events[event].iterations = ZERO;
                    }
                    break;
                default:
                    break;
                }
            }
        }
    }
}

void NTimer::start()
{
    for (uint8_t event = ZERO; event < eventsLength; event++)
    {
        events[event].enable = true;
        events[event].lastCallback = runtime;
    }
}

bool NTimer::start(uint8_t id)
{
    uint8_t event = search(id);
    if (event < eventsLength)
    {
        events[event].enable = true;
        events[event].lastCallback = runtime;
        return true;
    }
    return false;
}

bool NTimer::startCall(uint8_t id)
{
    uint8_t event = search(id);
    if (event < eventsLength)
    {
        events[event].lastCallback = runtime;
        events[event].enable = true;
        events[event].callback({runtime, &events[event]});
        events[event].iterations++;
        return true;
    }
    return false;
}

void NTimer::stop()
{
    for (uint8_t event = ZERO; event < eventsLength; event++)
    {
        events[event].enable = false;
        events[event].iterations = ZERO;
    }
}

bool NTimer::stop(uint8_t id, bool resetIterations = true)
{
    uint8_t event = search(id);
    if (event < eventsLength)
    {
        events[event].enable = false;
        if (resetIterations)
            events[event].iterations = ZERO;
        return true;
    }
    return false;
}

bool NTimer::call(uint8_t id)
{
    uint8_t event = search(id);
    if (event < eventsLength)
    {
        events[event].iterations++;
        events[event].callback(ElapsedEvent({runtime, &events[event]}));
        if (events[event].enable)
            events[event].lastCallback = runtime;
    }
    return false;
}

void NTimer::forceCall(uint8_t id)
{
    uint8_t event = search(id);
    if (event < eventsLength)
    {
        events[event].callback({runtime, &events[event]});
    }
}

void NTimer::delay(uint32_t ms, uint16_t id = 256)
{
    uint32_t start = runtime;
    while (true)
    {
        for (uint8_t event = ZERO; event < eventsLength; event++)
        {
            runtime = millis();
            if (runtime - start >= ms)
                return;

            if (events[event].id == id)
                continue;

            if (events[event].enable)
            {
                if (interval(events[event].lastCallback, events[event].time))
                {
                    events[event].callback({runtime, &events[event]});
                    events[event].iterations++;
                    switch (events[event].mode)
                    {
                    case ONCE:
                        events[event].enable = false;
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    }
}

pEvt NTimer::getEventSettings(uint8_t id)
{
    uint8_t event = search(id);
    if (event < eventsLength)
    {
        return &events[event];
    }
    return NULL;
}

void NTimer::operator+=(evt newEvent)
{
    addEvent(newEvent);
}

void NTimer::operator-=(uint8_t id)
{
    removeEvent(id);
}

pEvt NTimer::operator<<(uint8_t id)
{
    return getEventSettings(id);
}

void loop()
{
    runtime = millis();

    if (instance != ZERO)
    {
        instance->update();
    }
    NTimer_h_userLoop();
}