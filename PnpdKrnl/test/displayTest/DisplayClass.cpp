#include "DisplayClass.h"

DisplayClass::DisplayClass() 
:tftObj(TFT_CS, TFT_DC, TFT_RST)
{};

void DisplayClass::initializeDisplay() {
    tftObj.initR(INITR_REDTAB);
    tftObj.setRotation(3);
    tftObj.fillScreen(ST7735_BLACK);
};

void DisplayClass::justGetSomethingWorking(int displayDepth, int maxDepth, 
int timeMin, int timeSec) {
    
    tftObj.fillScreen(ST7735_BLACK);
    
    tftObj.setTextSize(2);
    tftObj.setCursor(0,0);
    tftObj.setTextColor(ST7735_RED);
    tftObj.print("At:");

    tftObj.setTextSize(5);
    tftObj.setCursor(0,20);
    tftObj.setTextColor(ST7735_RED);
    tftObj.print(displayDepth);

    tftObj.setTextSize(2);
    tftObj.setCursor(65,0);
    tftObj.setTextColor(ST7735_BLUE);
    tftObj.print("Most:");

    tftObj.setTextSize(5);
    tftObj.setCursor(65,20);
    tftObj.setTextColor(ST7735_BLUE);
    tftObj.print(maxDepth);

    tftObj.setTextSize(2);
    tftObj.setTextColor(ST7735_GREEN);
    tftObj.setCursor(0,70);
    tftObj.print("Time:");

    tftObj.setTextSize(4);

    if (timeMin < 10) {
        tftObj.setCursor(0,90);
        tftObj.print("0");
        tftObj.setCursor(25,90);
        tftObj.print(timeMin);
    }
    else {
        tftObj.setCursor(0,90);
        tftObj.print(timeMin);
    }

    tftObj.setCursor(40,90);
    tftObj.print(":");

    if (timeSec < 10) {
        tftObj.setCursor(60,90);
        tftObj.print("0");
        tftObj.setCursor(80,90);
        tftObj.print(timeSec);
    }
    else {
        tftObj.setCursor(60,90);
        tftObj.print(timeSec);
    }

};
