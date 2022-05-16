#include <NTimer.h> //<- Library to include

int baudrate = 9600; //Serial.begin() baudrate.

int led1Pin = LED_BUILTIN; //LED 1 pin.
bool led1State = false; //LED 1 state.

int led1Interval = 500; //Interval to change LED 1 state.
int led1EventID = 0; //Uniqe event ID for LED 1's event.
Event led1Event; //Event object for LED 1, set later.

int led2Pin = 10; //LED 2 pin.
bool led2State = false; //LED 2 state.

int led2Interval = 1s; //Interval to change LED 2 state. Using hz returns time in milliseconds.
int led2EventID = 1; //Uniqe event ID for LED 2's event.
Event led2Event; //Event object for LED 2, set later.

int sensorPin = A1; //Fictonal sensor, or real if you want to use one.
int sensorReading = 0; //Sensor reading.

int sensorPollingInterval = 20hz; //Interval to get the sensor reading. Usage of hz returns time in ms.
int sensorEventID = 2; //Uniqe event ID for the sensor's event.
Event sensorEvent; //Event object for the sensor, set later.

unsigned long time = 0; //Your object that saves from {millis()} through {NTimer.runtime}.

void led1IntervalCallback(ElapsedEvent eventInfo) //Your function that runs on your set interval. Must have 1 argument of {ElapsedEvent}.
{
    led1State = !led1State; //Logical Not LED 1's state.
    digitalWrite(led1Pin, led1State); //Write the new state.
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
    Serial.println(sensorReading); //Print.
}

void setup()
{
    pinMode(led1Pin, OUTPUT); //Set LED 1's pin to output.
    pinMode(led2Pin, OUTPUT); //Set LED 1's pin to output.

    led1Event = Event(led1EventID, led1Interval, led1IntervalCallback); //Setting LED 1's event to a new event that has the ID of {led1EventID}, interval of {led1Interval} and the callback of {led1IntervalCallback}.
    led2Event = Event(led2EventID, led2Interval, led2IntervalCallback); //Setting LED 2's event to a new event that has the ID of {led2EventID}, interval of {led2Interval} and the callback of {led2IntervalCallback}.
    sensorEvent = Event(sensorEventID, sensorPollingInterval, sensorReadCallback); //Setting the sensors event to a new event that has the ID of {sensorEventID}, interval of {sensorPollingInterval} and the callback of {sensorReadCallback}.

    NTimer.addEvent(led1Event); //Registering the event.
    NTimer.addEvent(led2Event); //Registering the event.
    NTimer.addEvent(sensorEvent); //Registering the event.

    NTimer.start(led1EventID); //Starting the event with the given ID, in this case it is the ID of LED 1.
    NTimer.start(); //Starting all Events.

    Serial.begin(baudrate); //Begin Serial.
}

void loop()
{
    NTimer.update(); //Checks which events are to run, also update NTimer.runtime that you can use.
    time = NTimer.runtime; //Saves {runtime} which is actually just {millis()}.
}