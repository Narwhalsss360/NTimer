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

#ifdef NPush_h
#warning Move NPush.h include BELOW NTimer.h for optimization.
#endif

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
    void stop();
    bool stop(uint8_t, bool = true);
    void update();
    bool call(uint8_t);
    void forceCall(uint8_t);
    void delay(uint32_t, uint16_t = 256);
    pEvt getEventSettings(uint8_t);
    ~NTimer();
};

extern void NTimer_h_userLoop();

#ifndef NTimer_cpp
#define loop NTimer_h_userLoop
#endif

#endif