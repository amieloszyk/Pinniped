/**************************************************
    This is just me playing with the display to 
    learn more about how it works    
**************************************************/

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SD.h>
#include <SPI.h>

#include "DisplayClass.h"
#include "SensorClass.h"

bool atSurface = true;
int currDepth = 0;
int maxDepth = 0;
int botTimeMin = 0;
int botTimeSec = 0;
int dispTimeMin = 0;
int dispTimeSec = 0;
int dispTemp = 0;
int tStepMilSec = 1000;

DisplayClass dispObj;
SensorClass sensorObj;
float press = 0.0;
float temp = 0.0;
float surfPress = 0.0;

void setup(void)    {
    dispObj.initializeDisplay();
    sensorObj.updateSensor();
    press = sensorObj.getPress();
    temp = sensorObj.getTemp();
    surfPress = press;
    Serial.begin(9600);
};

void loop() {
    
    sensorObj.updateSensor();
    press = sensorObj.getPress();
    temp = sensorObj.getTemp();

    currDepth = (press-surfPress)/1000*33;
    dispTemp = temp*9/5+32;
    
    if (currDepth <= 1) {
        atSurface = true;
        botTimeMin = 0;
        botTimeSec = 0;
    }
    else {
        atSurface = false;
    }

    if (! atSurface) {
        botTimeSec += tStepMilSec/1000;
        if (botTimeSec >= 60) {
            botTimeSec = 0;
            ++botTimeMin;
        }
        dispTimeSec = botTimeSec;
        dispTimeMin = botTimeMin;

        if (currDepth > maxDepth) {
            maxDepth = currDepth;
        }
    }

    dispObj.justGetSomethingWorking(currDepth, maxDepth, dispTimeMin, dispTimeSec, dispTemp);
    
    delay(tStepMilSec);
};
