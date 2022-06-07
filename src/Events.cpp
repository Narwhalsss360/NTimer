#include "Events.h"

ElapsedEvent::ElapsedEvent()
    :signalTime(NULL), pEventSettings(NULL)
{
}

ElapsedEvent::ElapsedEvent(uint32_t _signalTime, Event *_pEventSettings)
    :signalTime(_signalTime), pEventSettings(_pEventSettings)
{
}

Event::Event()
    : time(NULL), callback(NULL), lastCallback(ZERO), enable(false), iterations(ZERO)
{
}

Event::Event(uint8_t _id, uint32_t _time, void (*cb)(ElapsedEvent))
    : Event(_id, PERIODIC, _time, cb)
{
}

Event::Event(uint8_t _id, uint8_t _mode, uint32_t _time, void (*cb)(ElapsedEvent))
    : id(_id), mode(_mode),time(_time), callback(cb), lastCallback(millis()), enable(false), iterations(ZERO)
{
}