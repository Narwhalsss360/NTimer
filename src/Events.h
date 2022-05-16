#ifndef Events_h
#define Events_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <NDefs.h>

#define INVALID_EVENT(event) (event.time <= NULL || event.id == NULL) ? true : false

struct ElapsedEvent
{
    uint8_t id;
    uint32_t signalTime;
};

struct Event
{
    uint8_t id;
    bool enable;
    uint32_t time;
    uint32_t lastCallback;
    void (*callback)(ElapsedEvent);
    Event();
    Event(uint8_t, uint32_t, void (*)(ElapsedEvent));
};

typedef Event evt;
typedef evt *pEvt;
typedef evt &rEvt;

#endif