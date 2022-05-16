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

class NTimerClass
{
private:
    uint8_t timers;
    pEvt events;
    uint8_t search(uint8_t);
public:
    uint32_t runtime;
    NTimerClass();
    bool newTimer(evt);
    bool changeTimer(evt &);
    bool removeTimer(uint8_t);
    void start();
    bool start(uint8_t);
    void stop();
    bool stop(uint8_t);
    void update();
    ~NTimerClass();
};

extern NTimerClass NTimer;

#endif