#include "DisplayClass.h"

DisplayClass::DisplayClass() 
:tftObj(TFT_CS, TFT_DC, TFT_RST)
{};

void DisplayClass::initializeDisplay() {
    tftObj.initR(INITR_BLACKTAB);
    tftObj.setRotation(3);
    tftObj.fillScreen(ST7735_BLACK);
};

void DisplayClass::justGetSomethingWorking(int displayDepth, int maxDepth, 
int timeMin, int timeSec, int tempF) {
    
    // This should only black out old values
    tftObj.fillScreen(ST7735_BLACK);
    
    tftObj.setTextSize(2);
    tftObj.setCursor(0,0);
    tftObj.setTextColor(RED);
    tftObj.print("Depth");

    tftObj.setTextSize(4);
    tftObj.setCursor(4,18);
    tftObj.print(displayDepth);

    tftObj.setTextSize(1);
    tftObj.setTextColor(BLUE);    
    tftObj.setCursor(4,48);
    tftObj.print("MAX:");
    tftObj.setTextSize(2);
    tftObj.setCursor(28,48);
    tftObj.print(maxDepth);

    tftObj.setTextSize(2);
    tftObj.setTextColor(GREEN);
    tftObj.setCursor(0,64);
    tftObj.print("TimeLeft");
    //tftObj.print("SafeStop");
    
    tftObj.setTextSize(4);
    tftObj.setCursor(4,80);
    tftObj.print("---");//timeRem);

    tftObj.setTextColor(CYAN);
    tftObj.setTextSize(1);
    tftObj.setCursor(1,45+61);
    tftObj.print("B");
    tftObj.setCursor(1,53+61);
    tftObj.print("O");
    tftObj.setCursor(1,61+61);
    tftObj.print("T");
    
    tftObj.setTextSize(2);

    if (timeMin < 10) {
        tftObj.setCursor(7,113);
        tftObj.print("0");
        tftObj.setCursor(19,113);
        tftObj.print(timeMin);
    }
    else {
        tftObj.setCursor(7,113);
        tftObj.print(timeMin);
    }

    tftObj.setCursor(29,113);
    tftObj.print(":");

    if (timeSec < 10) {
        tftObj.setCursor(39,113);
        tftObj.print("0");
        tftObj.setCursor(51,113);
        tftObj.print(timeSec);
    }
    else {
        tftObj.setCursor(39,113);
        tftObj.print(timeSec);
    }
    
    tftObj.setTextColor(WHITE);
    tftObj.setTextSize(1);
    tftObj.setCursor(70,106);
    tftObj.print("T");
    tftObj.setCursor(70,114);
    tftObj.print("M");
    tftObj.setCursor(70,122);
    tftObj.print("P");

    tftObj.setTextSize(2);
    tftObj.setCursor(76,110);
    tftObj.print(tempF);


    //Plot compartment bars
    //Plot asscent rate

};
