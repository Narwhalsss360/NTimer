#include <NTimer.h>
#include <EEPROM.h>

#define WAIT_FOR_SERIAL 1000

NTimer timer;

int baudrate = 9600;

int sensorPin = A1;
int sensorInterval = 5m;
int sensorMode = PERIODIC;
int sensorEventId = 0;
NTimerEvent sensorEvent;

int memCounter = 0;

void clearEEPROM(byte fill) //Clears memory, fills memory with {fill} parameter.
{
    for (int i = 0; i < EEPROM.length(); i++)
    {
        EEPROM.update(i, fill);
    }
}

void printValues()
{
    for (int i = 0; i < EEPROM.length(); i++)
    {
        Serial.print("Minute ");
        Serial.print(i * 5);
        Serial.print(": ");
        Serial.println(EEPROM.read(i));
    }
}

byte getSensorReading()
{
    return map(analogRead(sensorPin), 0, 1023, 0, 255); //Get sensor reading from 0 - 255.
}

void save(ElapsedEvent eventInfo)
{
    if (memCounter == EEPROM.length()) //If EEPROM is filled, dont add anymore.
        return;
    EEPROM.update(memCounter, getSensorReading()); //Add sensor reading.
    memCounter++; //Count up.
}

void setup()
{
    Serial.begin(baudrate); //Start Serial.
    delay(WAIT_FOR_SERIAL); //Wait a little.

    if (Serial) //Execute block if Serial is connected at startup. Press reset button while connected.
    {
        printValues(); //Print values on EEPROM.
        clearEEPROM(0xff); //Clear after person checks.
        while (1) //Dont continue.
        {
        }
    }
    Serial.end(); //End Serial if not connected at startup.

    sensorEvent = NTimerEvent(sensorEventId, sensorMode, sensorInterval, save); //Set event.
    timer.addEvent(sensorEvent); //Register event.
    timer.start(sensorEventId, CALL); //Start timer and call at start.
}

void loop()
{
}