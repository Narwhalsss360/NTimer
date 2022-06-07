#ifndef NTimer_h
#define NTimer_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#ifndef MAX_INSTANCES
#define MAX_INSTANCES 4
#endif

#include <NDefs.h>
#include "Events.h"
#include "TimeLiterals.h"

extern uint32_t runtime;

inline bool interval(uint32_t &, uint32_t);

class NTimer
{
private:
    uint8_t eventsLength;
    pEvt events;
    uint8_t search(uint8_t);

public:
    NTimer();
    bool addEvent(evt);
    bool changeEvent(evt);
    bool removeEvent(uint8_t);
    void start();
    bool start(uint8_t);
    bool startCall(uint8_t);
    void stop(bool = true);
    bool stop(uint8_t, bool = true);
    void update();
    pEvt getEventSettings(uint8_t);
    ~NTimer();
};

extern void userLoop();

#ifndef NTimer_cpp
#define loop userLoop
#endif

#endif