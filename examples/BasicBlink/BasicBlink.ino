#include <NTimer.h> //<- Library to include

#define LED_INTERVAL (500_ms)

bool state = false; //State of led.

//ntime_t is the data type for all timing objects
/*
    ntime_t uses microseconds as its tick
    operators are:
    _hz
    _ms
    _s
    _m
    _h
*/
ntime_t lastTimeStateChange = 0; //Last time state was changed. Automatically updated in interval function.

void onInterval()
{
    state = !state; //Flip the state.
    digitalWrite(LED_BUILTIN, state); //Write the new state.
}

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT); //Set as output.
}

void loop()
{
    if (intervalElapsed(lastTimeStateChange, LED_INTERVAL)) //Check if its time to blink led.
    {
        onInterval(); //Change the state of the led.
    }
    ntime_t uptimeInMicroseconds = uptime();
}