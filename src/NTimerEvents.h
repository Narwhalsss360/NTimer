#ifndef Events_h
#define Events_h

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <NDefs.h>

#define INVALID_EVENT(event) (event.time <= NULL || event.id == NULL) ? true : false
#define INVALID_ELAPSED_EVENT(elapsedEvent) (elapsedEvent.signalTime == 0 || elapsedEvent.pEventSettings == 0) ? true : false

enum EVENTMODES
{
    ONCE,
    PERIODIC,
    ITERATION_COUNT
};

typedef struct NTimerEvent;

struct ElapsedEvent
{
    uint32_t signalTime;
    NTimerEvent *pEventSettings;
    ElapsedEvent();
    ElapsedEvent(uint32_t, NTimerEvent *);
};

struct NTimerEvent
{
    uint8_t id;
    bool enable;
    uint32_t time;
    uint8_t mode;
    uint32_t iterations;
    uint32_t maxIterations;
    uint32_t lastCallback;
    void (*callback)(ElapsedEvent);
    NTimerEvent();
    NTimerEvent(uint8_t, uint32_t, void (*)(ElapsedEvent));
    NTimerEvent(uint8_t, uint8_t, uint32_t, void (*)(ElapsedEvent));
    NTimerEvent(uint8_t, uint8_t, uint32_t, uint32_t, void (*)(ElapsedEvent));
};

typedef NTimerEvent evt;
typedef evt &rEvt;
typedef evt *pEvt;

#endif