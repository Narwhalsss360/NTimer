#ifndef PerfTimer_h
#define PerfTimer_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <NDefs.h>

struct PerfTimer
{
private:
    unsigned long (*timeFunction) (void);
    bool running = false;
public:
    uint32_t startTime = ZERO;
    uint32_t totalTime = ZERO;

    void start();
    void stop();
    PerfTimer(bool = true, unsigned long (*) (void) = millis);
};

typedef PerfTimer PT;
#endif