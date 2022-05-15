#include <NTimer.h>

#define LED_PIN 9
#define LED_EVENT_ID 0
#define LED_INTERVAL 1_s

evt ledEvent(0, 1_s, interval);
bool state = false;

void interval(ElapsedEvent info)
{
    state = !state;
    digitalWrite(LED_PIN, state);
}

void setup()
{
    pinMode(LED_PIN, OUTPUT);
    NTimer.newTimer(ledEvent);
    NTimer.start();
}

void loop()
{
    NTimer.update();
}