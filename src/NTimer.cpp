#define NTimer_cpp
#include "NTimer.h"

uint32_t runtime;
static NTimer *instances[MAX_INSTANCES] = { ZERO };

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
    for (uint8_t instance = ZERO; instance < MAX_INSTANCES; instance++)
    {
        if (instances[instance] == ZERO)
        {
            instances[instance] = this;
            return;
        }
    }
}

NTimer::~NTimer()
{
    free(events);
    for (uint8_t instance = ZERO; instance < MAX_INSTANCES; instance++)
    {
        if (instances[instance] == this)
        {
            instances[instance] = ZERO;
        }
    }
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

bool NTimer::changeEvent(evt event)
{
    uint8_t event = search(event.id);
    if (event < eventsLength)
    {
        if (events[event].enable)
            event.enable = true;
        events[event] = event;
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
                events[event].iterations++;
                events[event].callback({runtime, &events[event]});
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
        events[event].enable = true;
        events[event].iterations++;
        events[event].callback({runtime, &events[event]});
        events[event].lastCallback = runtime;
        return true;
    }
    return false;
}

void NTimer::stop(bool resetIterations = true)
{
    for (uint8_t event = ZERO; event < eventsLength; event++)
    {
        events[event].enable = false;
        if (resetIterations)
            events[index].iterations = ZERO;
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

pEvt NTimer::getEventSettings(uint8_t id)
{
    uint8_t event = search(id);
    if (event < eventsLength)
    {
        return &events[event];
    }
    return NULL;
}

NTimer::~NTimer()
{
    delete [] events;
}

void loop()
{
    runtime = millis();

    if (instances[ZERO] == ZERO)
    {
        userLoop();
        return;
    }
    else
    {
        instances[ZERO]->update();
    }

    for (uint8_t instance = 1; instance < MAX_INSTANCES; instance++)
    {
        if (instances[instance] == ZERO)
            break;
        instances[instance]->update();
    }
    userLoop();
}