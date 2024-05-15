#ifndef DelayAsync_h
#define DelayAsync_h

#include "TimeTypes.h"
#include <NEvents.h>

class AsynchronusDelayInfo;

using AsynchronusDelayInfoHandler = void (*)(AsynchronusDelayInfo* sender);

AsynchronusDelayInfo* delayAsync(ntime_t delay, AsynchronusDelayInfoHandler handler = nullptr, void* context = nullptr);

void checkAsynchronusDelays();

class AsynchronusDelayInfo
{
public:
    AsynchronusDelayInfo(ntime_t delay, AsynchronusDelayInfoHandler handler = nullptr, void* context = nullptr);

    bool run();

    ntime_t delay() const;

    ntime_t startTime() const;

    const void* context() const;

    void* context();

    bool bound() const;

    ~AsynchronusDelayInfo();

    Event<AsynchronusDelayInfo, AsynchronusDelayInfo*> continueWith;

private:
    ntime_t _startTime, _delay;
    void* _context;
};

#endif
