#include <Arduino.h>
#include <SevSeg.h>
#include <DHT.h>

#define DHTPIN A0
DHT dht(DHTPIN, DHT11);

SevSeg sevseg;

void setup() {
    byte numDigits = 4;
    byte digitPins[] = {2, 3, 4, 5};
    byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
    sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins, true);
    sevseg.setBrightness(100);
    dht.begin();
}

void loop() {
    int temp = dht.readTemperature();
    int hum = dht.readHumidity();
    char outBuff[8];
    sprintf(outBuff, "%d.%d", temp, hum);
    sevseg.setChars(outBuff);
    sevseg.refreshDisplay();
}