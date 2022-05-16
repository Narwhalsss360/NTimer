#ifndef NTimer_h
#define NTimer_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <NDefs.h>
#include "Events.h"
#include "TimeLiterals.h"

bool interval(uint32_t &, uint32_t);

class NTimerClass
{
private:
    uint8_t eventsLength;
    pEvt events;
    uint8_t search(uint8_t);

public:
    uint32_t runtime;
    NTimerClass();
    bool addEvent(evt);
    bool changeEvent(evt);
    bool removeEvent(uint8_t);
    void start();
    bool start(uint8_t);
    void stop();
    bool stop(uint8_t);
    void update();
    ~NTimerClass();
};

extern NTimerClass NTimer;

#endif