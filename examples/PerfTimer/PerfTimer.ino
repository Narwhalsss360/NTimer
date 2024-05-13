#include <PerfTimer.h>

// PerfTimer has no safeties, worst case, totalTime is some crazy number.

int baudrate = 9600;

PerfTimer t1(false); //Dont start right away.

void setup()
{
    Serial.begin(baudrate);
}

void loop()
{
    t1.start();
    delay(800); //Task 1 to time.
    t1.stop();
    Serial.println("Task 1: " + String(t1.totalTime) + "milliseconds");

    PerfTimer t2(true, micros) //Start right away using micros as the timing function.
    delayMicroseconds(700); //Task 2 to time.
    t2.stop();
    Serial.println("Task 2: " + String(t2.totalTime) + "microseconds");
}