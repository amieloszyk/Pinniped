/**************************************************
    This is just me playing with the display to 
    learn more about how it works    
**************************************************/

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SD.h>
#include <SPI.h>

#include "DisplayClass.h"
/*
// TFT display and SD card will share the hardware SPI interface.
// Hardware SPI pins are specific to the Arduino board type and
// cannot be remapped to alternate pins.  For Arduino Uno,
// Duemilanove, etc., pin 11 = MOSI, pin 12 = MISO, pin 13 = SCK.
#define SD_CS    4  // Chip select line for SD card
#define TFT_CS  10  // Chip select line for TFT display
#define TFT_DC   8  // Data/command line for TFT
#define TFT_RST  -1  // Reset line for TFT (or connect to +5V)
*/

int depth = 0;
int timeMin = 0;
int timeSec = 0;
int tStepMilSec = 1000;

DisplayClass dispObj;

void setup(void)    {
    dispObj.initializeDisplay();
};

void loop() {
    
    delay(tStepMilSec);
    ++depth;
    timeSec += tStepMilSec/1000;
    if (timeSec >= 60) {
        timeSec = 0;
        ++timeMin;
    }
    dispObj.justGetSomethingWorking(depth, 20, timeMin, timeSec);
};
