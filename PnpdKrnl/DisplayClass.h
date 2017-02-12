/*
Dive computer display:
160x128 (There is a issue somewhere, and the screen 
is only 128x128 and not aligned right)
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

// Color definitions
#define	BLACK   0x0000
#define	RED     0x001F
#define	BLUE    0xF800
#define	GREEN   0x07E0
#define YELLOW    0x07FF
#define MAGENTA 0xF81F
#define CYAN  0xFFE0
#define WHITE   0xFFFF

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

        void justGetSomethingWorking(int displayDepth, int maxDepthint, int timeMin, int timeSec, int tempF);

};

