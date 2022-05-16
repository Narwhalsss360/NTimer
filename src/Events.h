#ifndef Events_h
#define Events_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <NDefs.h>

#define INVALID_EVENT(event) (event.time <= NULL || event.id == NULL) ? true : false

enum MODES
{
    ONCE,
    PERIODIC
};

typedef struct Event;

struct ElapsedEvent
{
    uint32_t signalTime;
    Event *pEventSettings;
};

struct Event
{
    uint8_t id;
    bool enable;
    uint32_t time;
    uint8_t mode;
    uint32_t lastCallback;
    void (*callback)(ElapsedEvent);
    Event();
    Event(uint8_t, uint32_t, void (*)(ElapsedEvent));
    Event(uint8_t, uint8_t, uint32_t, void (*)(ElapsedEvent));
};

typedef Event evt;
typedef evt &rEvt;
typedef evt *pEvt;

#endif