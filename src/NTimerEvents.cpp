#include "NTimerEvents.h"

ElapsedEvent::ElapsedEvent()
    :signalTime(NULL), pEventSettings(NULL)
{
}

ElapsedEvent::ElapsedEvent(uint32_t _signalTime, NTimerEvent *_pEventSettings)
    :signalTime(_signalTime), pEventSettings(_pEventSettings)
{
}

NTimerEvent::NTimerEvent()
    : time(NULL), callback(NULL), lastCallback(ZERO), enable(false), iterations(ZERO), maxIterations(ZERO)
{
}

NTimerEvent::NTimerEvent(uint8_t _id, uint32_t _time, void (*cb)(ElapsedEvent))
    : id(_id), mode(PERIODIC), time(_time), callback(cb), lastCallback(millis()), enable(false), iterations(ZERO), maxIterations(ZERO)
{
}

NTimerEvent::NTimerEvent(uint8_t _id, uint8_t _mode, uint32_t _time, void (*cb)(ElapsedEvent))
    : id(_id), mode(_mode), time(_time), callback(cb), lastCallback(millis()), enable(false), iterations(ZERO), maxIterations(ZERO)
{
}

NTimerEvent::NTimerEvent(uint8_t _id, uint8_t _mode, uint32_t _maxIterations, uint32_t _time, void (*cb)(ElapsedEvent))
    : id(_id), mode(_mode), time(_time), callback(cb), lastCallback(millis()), enable(false), iterations(ZERO), maxIterations(_maxIterations)
{
}