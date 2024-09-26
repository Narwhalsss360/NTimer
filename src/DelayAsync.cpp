#include "DelayAsync.h"
#include "Uptime.h"
#include <stdcol.h>
#include <SketchBoundLibrary.h>

using namespace stdcol::operators;
using stdcol::dynamic_array;
using stdcol::iterate;
using stdcol::size;

static dynamic_array<AsynchronusDelayInfo*> activeDelays;

static bool checkBound = addSketchBinding(bind_loop, &invokable_get(checkAsynchronusDelays));

AsynchronusDelayInfo* delayAsync(ntime_t delay, AsynchronusDelayInfoHandler handler, void* context)
{
    return new AsynchronusDelayInfo(delay, handler, context);
}

void checkAsynchronusDelays()
{
    for (stdcol::index i = 0; i < size(activeDelays); i++)
    {
        if (activeDelays[i]->run())
        {
            delete activeDelays[i];
            activeDelays.remove(i);
        }
    }
    activeDelays.reserve(size(activeDelays));
}

AsynchronusDelayInfo::AsynchronusDelayInfo(ntime_t delay, AsynchronusDelayInfoHandler handler, void* context)
    : continueWith(Event<AsynchronusDelayInfo, AsynchronusDelayInfo*>()), _startTime(uptime()), _delay(delay), _context(context)
{
    continueWith += handler;
    activeDelays += this;
}

bool AsynchronusDelayInfo::run()
{
    if (uptime() - _startTime < _delay)
        return false;

    continueWith(this);
    return true;
}

ntime_t AsynchronusDelayInfo::delay() const
{
    return _delay;
}

ntime_t AsynchronusDelayInfo::startTime() const
{
    return _startTime;
}

const void* AsynchronusDelayInfo::context() const
{
    return _context;
}

void* AsynchronusDelayInfo::context()
{
    return _context;
}

bool AsynchronusDelayInfo::bound() const {
    return checkBound;
}

AsynchronusDelayInfo::~AsynchronusDelayInfo()
{
    activeDelays -= this;
}
