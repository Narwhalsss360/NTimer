#include <LiteTimer.h>

LiteTimer sendMessageTimer(2s, START); // New timer that runs every 2 seconds and starts right away. you can use literals s, m, and hz.

bool ledState = false;
LiteTimer toggleLedStateTimer(2hz);

void setup()
{
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);

    //Class members that can be useful.
    toggleLedStateTimer.stop(); // Stops timer.
    toggleLedStateTimer.enabled; // bool variable that is true when timer is enabled.
    toggleLedStateTimer.tickInterval; // uint32_t that is the tick interval.
    toggleLedStateTimer.lastTick; // Last tick time.

    toggleLedStateTimer.start(); // Starts timer
}

void loop()
{
    if (sendMessageTimer) // Is true when its time to run the next timer tick.
    {
        Serial.print("Message timer tick at: ");
        Serial.println(millis());
    }

    if (toggleLedStateTimer)
    {
        ledState = !ledState; //Flip led state.
    }
    
    digitalWrite(LED_BUILTIN, ledState);
}