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

bool NTimer::changeEvent(evt event)
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

bool NTimer::removeEvent(uint8_t id)
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

uint8_t NTimer::search(uint8_t id)
{
    for (uint8_t i = ZERO; i < eventsLength; i++)
    {
        if (events[i].id == id)
            return i;
    }
    return eventsLength;
}

void NTimer::update()
{
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

void NTimer::start()
{
    for (uint8_t i = ZERO; i < eventsLength; i++)
    {
        events[i].enable = true;
        events[i].lastCallback = runtime;
    }
}

void NTimer::stop()
{
    for (uint8_t i = ZERO; i < eventsLength; i++)
    {
        events[i].enable = false;
    }
}

bool NTimer::start(uint8_t id)
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

bool NTimer::startCall(uint8_t id)
{
    uint8_t index = search(id);
    if (index < eventsLength)
    {
        events[index].enable = true;
        events[index].callback({runtime, &events[index]});
        events[index].lastCallback = runtime;
        return true;
    }
    return false;
}

bool NTimer::stop(uint8_t id)
{
    uint8_t index = search(id);
    if (index < eventsLength)
    {
        events[index].enable = false;
        return true;
    }
    return false;
}

pEvt NTimer::getEventSettings(uint8_t id)
{
    uint8_t index = search(id);
    if (index < eventsLength)
    {
        return &events[index];
    }
    return NULL;
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