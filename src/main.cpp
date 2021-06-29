#include <Arduino.h>
#include <SevSeg.h>
#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>

DHT dht(A0, DHT11);

OneWire oneWire(A1);
DallasTemperature ds(&oneWire);
unsigned long delayInMillis = 750;
unsigned long lastTempRequest = 0;

SevSeg sevseg;

void setup() {
    byte numDigits = 4;
    byte digitPins[] = {2, 3, 4, 5};
    byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
    sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins, true);
    sevseg.setBrightness(100);

    dht.begin();

    ds.begin();
    ds.setWaitForConversion(false);
}

void loop() {
    int temp;
    if (millis() - lastTempRequest >= delayInMillis) {
        ds.requestTemperatures();
        temp = ds.getTempCByIndex(0);
        lastTempRequest = millis(); 
    }
    // int temp = dht.readTemperature();
    int hum = dht.readHumidity();
    char outBuff[8];
    sprintf(outBuff, "%d.%d", temp, hum);
    sevseg.setChars(outBuff);
    sevseg.refreshDisplay();
}
