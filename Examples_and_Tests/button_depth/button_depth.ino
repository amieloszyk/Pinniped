/**************************************************
    This is just me playing with the display to 
    learn more about how it works    
**************************************************/

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SD.h>
#include <SPI.h>

// TFT display and SD card will share the hardware SPI interface.
// Hardware SPI pins are specific to the Arduino board type and
// cannot be remapped to alternate pins.  For Arduino Uno,
// Duemilanove, etc., pin 11 = MOSI, pin 12 = MISO, pin 13 = SCK.
#define SD_CS    4  // Chip select line for SD card
#define TFT_CS  10  // Chip select line for TFT display
#define TFT_DC   8  // Data/command line for TFT
#define TFT_RST  -1  // Reset line for TFT (or connect to +5V)

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

#define BUTTON_NONE 0
#define BUTTON_DOWN 1
#define BUTTON_RIGHT 2
#define BUTTON_SELECT 3
#define BUTTON_UP 4
#define BUTTON_LEFT 5

float depth=0;
int read_hist;

void setup(void)    {
    Serial.begin(9600);
    
    tft.initR(INITR_REDTAB);   // initialize a ST7735R chip, red tab
    
    Serial.println("Started up!");
    
    // Black screen
    tft.fillScreen(ST7735_BLACK);
    // Prep to display
    tft.setTextSize(5);
    tft.setCursor(20,20);
    tft.setTextColor(ST7735_RED);
    // Display
    tft.print(int(depth));
    
}

uint8_t readButton(void) {
  float a = analogRead(3);
  
  a *= 5.0;
  a /= 1024.0;
  
  Serial.print("Button read analog = ");
  Serial.println(a);
  if (a < 0.2) return BUTTON_DOWN;
  if (a < 1.0) return BUTTON_RIGHT;
  if (a < 1.5) return BUTTON_SELECT;
  if (a < 2.0) return BUTTON_UP;
  if (a < 3.2) return BUTTON_LEFT;
  else return BUTTON_NONE;
}

void loop() {
    
    // Read the buttons
    uint8_t temp_read=readButton();
    
    if (temp_read==BUTTON_DOWN) {
        depth+=1;
        read_hist=1;
        }
    else if (temp_read==BUTTON_UP) {
        depth-=1;
        read_hist=1;
        }
    else if (temp_read==BUTTON_SELECT) {
        depth=0.0;
        read_hist=1;
        }
    else {
        read_hist=0;
        }
    
    // Prep to display
    tft.setTextSize(5);
    tft.setCursor(20,20);
    tft.setTextColor(ST7735_RED);

    
    // If we read something, wait a sec
    if (read_hist==1)   {
    
        // Refresh screen
        tft.fillScreen(ST7735_BLACK);
        
        // Display
        tft.print(int(depth));
        }
}
