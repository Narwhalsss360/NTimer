#include "Events.h"

Event::Event()
    : time(NULL), callback(NULL), lastCallback(ZERO), enable(false)
{
}

Event::Event(uint8_t _id, uint32_t _time, void (*cb)(ElapsedEvent))
    : id(_id), time(_time), callback(cb), lastCallback(millis()), enable(false)
{
}