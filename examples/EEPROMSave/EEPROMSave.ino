#include <AutoBind.h> //<- This library uses SketchBinder to automatically update anything that updates every loop
#include <NTimer.h>
#include <EEPROM.h>

#define SENSOR_PIN (A0)
#define BAUDRATE (115200)
#define SERIAL_WAIT_TIME 1250

constexpr const ntime_t::int_type SAVE_INTERVAL = 1_m; //Declarating constexpr for ntime_t

uint16_t memoryUsed = 0;

void clearEEPROM()
{
    for (int i = 0; i < EEPROM.length(); i++)
    {
        EEPROM.update(i, 0xFF);
    }
}

void save(ElapsedEventArgs& args)
{
    if (memoryUsed == EEPROM.length()) //Memory full
        return;
    EEPROM.update(memCounter, analogRead(SENSOR_PIN));
    memoryUsed++;
}

void printValues()
{
    for (int i = 0; i < EEPROM.length(); i++)
    {
        Serial.print(i);
        Serial.print(':');
        Serial.println(EEPROM.read(i));
    }
}

TimedEvent saveEvent = TimedEvent(SAVE_INTERVAL, true); //Interval and auto reset

void setup()
{
    Serial.begin(BAUDRATE);
    delay(SERIAL_WAIT_TIME);
    if (Serial)
    {
        printValues();
        clearEEPROM();
        while (true);
    }
    Serial.end();
    saveEvent.elapsed += save;
    saveEvent.start();
}

void loop()
{
    //checkTimedEvents(); //If no AutoBind/SketchBinder, use this to check all timedevents
}
