/*
Dive computer display:
160x128
+-----------------------------------------------+
| (0,0) --->                                    |
|   y                                           |
|   |                                           |
|   V                                           |
|                                               |
|                                               |
|                                               |
+-----------------------------------------------+

*/

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SD.h>
#include <SPI.h>

#define SD_CS    4  // Chip select line for SD card
#define TFT_CS  10  // Chip select line for TFT display
#define TFT_DC   8  // Data/command line for TFT
#define TFT_RST  -1  // Reset line for TFT (or connect to +5V)Z

class DisplayClass {
    
    private:

        Adafruit_ST7735 tftObj;
        int draw;
        int elapsedMin;
        int elapsedSec;
        int bottomMinutes;
        float depthRateFtPerSec;

        void drawFrame();
        void drawDepth();
        void drawElapsedTime();
        void drawBottomTime();
        void drawDepthRate();

    public:

        DisplayClass();
        void initializeDisplay();
        void readButton();
        void setDispDepth(int depth);
        void setDispElapsedTime(int elapsedMin, int elapsedSec);
        void setBottomTime(int bottomMinutes);
        void setDepthRate(float depthRateFtPerSec);

        void justGetSomethingWorking(int displayDepth, int maxDepthint, int timeMin, int timeSec);

};

