#include <AutoBind.h> //<- This library uses SketchBinder to automatically update anything that updates every loop
#include <NTimer.h>

#define BAUDRATE 115200
#define BUTTON_PIN 3
#define BUTTON_MODE INPUT_PULLUP

void printHello(AsynchronusDelayInfo* info)
{
    void* context = nullptr;
    if (info != nullptr)
        context = info->context(); //Get context from caller

    Serial.println("Hello, 1 second later");
}

void checkButton(ElapsedEventArgs)
{
    bool activeState = BUTTON_MODE == INPUT_PULLUP ? 0 : 1;
    if (digitalRead(BUTTON_PIN) == activeState)
    {
        AsynchronusDelayInfo* info = delayAsync(1_s, printHello/*, nullptr*/); //Third argument is optional, it is context for handler
    }
}

TimedEvent buttonCheckEvent = TimedEvent(15_ms, true);

void setup()
{
    Serial.begin(BAUDRATE);
    pinMode(BUTTON_PIN, BUTTON_MODE);
    buttonCheckEvent.elapsed += checkButton;
    buttonCheckEvent.start();
}

void loop()
{
    //checkTimedEvents(); //If no AutoBind/SketchBinder, use this to check all timedevents
}
