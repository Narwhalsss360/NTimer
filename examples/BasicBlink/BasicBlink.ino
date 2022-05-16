#include <NTimer.h> //<- Library to include

const int ledInterval = 500; //Interval to blink led.

bool state = false; //State of led.

unsigned long lastTimeStateChange = 0; //Last time state was changed.

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
    NTimer.update(); //Update NTimer clocks.

    if (interval(lastTimeStateChange, ledInterval)) //Check if its time to blink led.
    {
        onInterval(); //Change the state of the led.
    }
}