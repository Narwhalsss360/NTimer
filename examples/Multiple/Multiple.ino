#include <NTimer.h> //<- Library to include

NTimer timer; //<- Your timer.

int baudrate = 9600; //Serial.begin() baudrate.

int led1Pin = LED_BUILTIN; //LED 1 pin.
bool led1State = false; //LED 1 state.

int led1Interval = 1s; //Interval to change LED 1 state. Usage of s returns time in ms.
int led1EventID = 0; //Uniqe event ID for LED 1's event.
int led1Mode = PERIODIC; //LED 1's mode, event occurs every interval.
NTimerEvent led1Event; //Event object for LED 1, set later.

int led2Pin = 10; //LED 2 pin.
bool led2State = false; //LED 2 state.

int led2Interval = 500; //Interval to change LED 2 state.
int led2EventID = 1; //Uniqe event ID for LED 2's event.
int led2Mode = ONCE; //LED 2's mode, event occurs only once after timer is started.
NTimerEvent led2Event; //Event object for LED 2, set later.

int sensorPin = A1; //Fictonal sensor, or real if you want to use one.
int sensorReading = 0; //Sensor reading.

int sensorPollingInterval = 20hz; //Interval to get the sensor reading. Usage of hz returns time in ms.
int sensorEventID = 2; //Uniqe event ID for the sensor's event.
int sensorMode = PERIODIC; //sensor's mode, event occurs every interval.
NTimerEvent sensorEvent; //Event object for the sensor, set later.

unsigned long time = 0; //Your object that saves from {millis()} through {NTimer.runtime}.

void led1IntervalCallback(ElapsedEvent eventInfo) //Your function that runs on your set interval. Must have 1 argument of {ElapsedEvent}.
{
    led1State = !led1State; //Logical Not LED 1's state.
    digitalWrite(led1Pin, led1State); //Write the new state.
    if (led1State)
    {
        timer.start(led2EventID); //Start LED 2's event, in this case, LED 2 will always change state 500 ms after LED 1 is on except for the first run.
    }
}

void led2IntervalCallback(ElapsedEvent eventInfo) //Your function that runs on your set interval. Must have 1 argument of {ElapsedEvent}.
{
    led2State = !led2State; //Logical Not LED 2's state.
    digitalWrite(led2Pin, led2State); //Write the new state.
}

void sensorReadCallback(ElapsedEvent eventInfo) //Your function that runs on your set interval. Must have 1 argument of {ElapsedEvent}.
{
    sensorReading = analogRead(sensorPin); //Read the sensor.
    Serial.print("Sensor Reading at "); //Print.
    Serial.print(eventInfo.signalTime); // {ElapsedEvent.signalTime} returns the time that the sensor was polled.
    Serial.print(", Value: "); //Print.
    Serial.print(sensorReading); //Print.
    Serial.print(", Event ID: "); //Print
    Serial.println(eventInfo.pEventSettings->id); //{ElapsedEvent} has a pointer to the event settings that called this event.
}

void setup()
{
    pinMode(led1Pin, OUTPUT); //Set LED 1's pin to output.
    pinMode(led2Pin, OUTPUT); //Set LED 1's pin to output.

    led1Event = NTimerEvent(led1EventID, led1Mode,led1Interval, led1IntervalCallback); //Setting LED 1's event to a new event that has the ID of {led1EventID}, {led1Mode} mode, interval of {led1Interval} and the callback of {led1IntervalCallback}.
    led2Event = NTimerEvent(led2EventID, led2Mode,led2Interval, led2IntervalCallback); //Setting LED 2's event to a new event that has the ID of {led2EventID}, {led2Mode} mode, interval of {led2Interval} and the callback of {led2IntervalCallback}.
    sensorEvent = NTimerEvent(sensorEventID, sensorMode,sensorPollingInterval, sensorReadCallback); //Setting the sensors event to a new event that has the ID of {sensorEventID}, {sensorMode} mode, ,interval of {sensorPollingInterval} and the callback of {sensorReadCallback}.

    timer.addEvent(led1Event); //Registering the event.
    timer.addEvent(led2Event); //Registering the event.
    timer.addEvent(sensorEvent); //Registering the event.

    timer.start(led1EventID); //Starting the event with the given ID, in this case it is the ID of LED 1.
    timer.start(); //Starting all Events.

    Serial.begin(baudrate); //Begin Serial.
}

void loop()
{
    time = runtime; //Saves {runtime} into {time} which is actually just {millis()}. Just use runtime instead of millis() for your millis() needs.
}