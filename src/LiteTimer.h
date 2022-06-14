#ifndef LiteTimer_h
#define LiteTimer_h

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <NDefs.h>
#include "TimeLiterals.h"

#define START true

class LiteTimer
{
public:
    bool enabled;
    uint32_t lastTick;
    uint32_t tickInterval;

    LiteTimer(uint32_t = ZERO, bool = true);
    void start();
    void stop();
    operator bool();
    ~LiteTimer();
};

#endif