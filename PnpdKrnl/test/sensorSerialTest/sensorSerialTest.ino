/* 
This script tests that the depth sensor is appropriately integrated.

@author: Alexander J. Mieloszyk
Created on: January 29th, 2017
*/

#include "SensorClass.h"
#include <SPI.h>

SensorClass sensorObj;
float press = 0.0;
float temp = 0.0;

void setup() {
    Serial.begin(9600);
    delay(100);
};

void loop() {
    sensorObj.updateSensor();
    press = sensorObj.getPress();
    temp = sensorObj.getTemp();

    Serial.print("Pressure = ");
    Serial.print(press);
    Serial.println(" mbar");
    
    Serial.print("Temperature = ");
    Serial.print(temp);
    Serial.println("C");

    Serial.println("------------------");
    Serial.println(" ");

    //sensorObj.printData();
    delay(3000);
};
