

#include <SPI.h>
#include "arduino.h"
#include "SensorClass.h"

SensorClass::SensorClass() {
    setupSensor();
};

void SensorClass::resetSensor() {
    /* 
    Reset the sensor
    */

    SPI.setDataMode(SPI_MODE0); 
    SPI.transfer(0x15);
    SPI.transfer(0x55);
    SPI.transfer(0x40);
};

void SensorClass::setupSensor() {
    /*
    Setup up the sensor I/O
    */

    clockPin = 9;
    SPI.begin(); //see SPI library details on arduino.cc for details
    SPI.setBitOrder(MSBFIRST);
    SPI.setClockDivider(SPI_CLOCK_DIV32); //divide 16 MHz to communicate on 500 kHz
    pinMode(clockPin, OUTPUT);
};

void SensorClass::setCalibrationWords() {
    /*
    Get the calibration words
    */

    TCCR1B = (TCCR1B & 0xF8) | 1 ; //generates the MCKL signal
    analogWrite (clockPin, 128) ; 

    resetSensor();//resets the sensor - caution: afterwards mode = SPI_MODE0!

    //Calibration word 1
    unsigned int inbyte1 = 0;
    SPI.transfer(0x1D); //send first byte of command to get calibration word 1
    SPI.transfer(0x50); //send second byte of command to get calibration word 1
    SPI.setDataMode(SPI_MODE1); //change mode in order to listen
    calibrationWordOne = SPI.transfer(0x00); //send dummy byte to read first byte of word
    calibrationWordOne = calibrationWordOne << 8; //shift returned byte 
    inbyte1 = SPI.transfer(0x00); //send dummy byte to read second byte of word
    calibrationWordOne = calibrationWordOne | inbyte1; //combine first and second byte of word
    //Serial.print("Calibration word 1 =");
    //Serial.println(calibrationWordOne); 

    resetSensor();//resets the sensor

    //Calibration word 2; see comments on calibration word 1
    byte inbyte2 = 0; 
    SPI.transfer(0x1D);
    SPI.transfer(0x60);
    SPI.setDataMode(SPI_MODE1); 
    calibrationWordTwo = SPI.transfer(0x00);
    calibrationWordTwo = calibrationWordTwo <<8;
    inbyte2 = SPI.transfer(0x00);
    calibrationWordTwo = calibrationWordTwo | inbyte2;
    //Serial.print("Calibration word 2 =");
    //Serial.println(calibrationWordTwo);   

    resetSensor();//resets the sensor

    //Calibration word 3; see comments on calibration word 1
    byte inbyte3 = 0;
    SPI.transfer(0x1D);
    SPI.transfer(0x90); 
    SPI.setDataMode(SPI_MODE1); 
    calibrationWordThree = SPI.transfer(0x00);
    calibrationWordThree = calibrationWordThree <<8;
    inbyte3 = SPI.transfer(0x00);
    calibrationWordThree = calibrationWordThree | inbyte3;
    //Serial.print("Calibration word 3 =");
    //Serial.println(calibrationWordThree);  

    resetSensor();//resets the sensor

    //Calibration word 4; see comments on calibration word 1
    byte inbyte4 = 0;
    SPI.transfer(0x1D);
    SPI.transfer(0xA0);
    SPI.setDataMode(SPI_MODE1); 
    calibrationWordFour = SPI.transfer(0x00);
    calibrationWordFour = calibrationWordFour <<8;
    inbyte4 = SPI.transfer(0x00);
    calibrationWordFour = calibrationWordFour | inbyte4;
    //Serial.print("Calibration word 4 =");
    //Serial.println(calibrationWordFour); 

};

void SensorClass::setCalibrationFactors(){
    /* 
    Do some bitshifting to extract the calibration factors 
    out of the calibration words; read datasheet AN510 for better understanding
    */

    calibrationFactorOne = calibrationWordOne >> 3 & 0x1FFF;
    calibrationFactorTwo = ((calibrationWordOne & 0x07) << 10) | ((calibrationWordTwo >> 6) & 0x03FF);;
    calibrationFactorThree = (calibrationWordThree >> 6) & 0x03FF;
    calibrationFactorFour = (calibrationWordFour >> 7) & 0x07FF;
    calibrationFactorFive = ((calibrationWordTwo & 0x003F) << 6) | (calibrationWordThree & 0x003F);
    calibrationFactorSix = calibrationWordFour & 0x007F;

    resetSensor();//resets the sensor
};

int SensorClass::getRawTemp() {
    /*
    Return the raw temperature value
    */
    
    unsigned int tempMSB = 0; //first byte of value
    unsigned int tempLSB = 0; //last byte of value
    int rawTemp = 0;
    SPI.transfer(0x0F); //send first byte of command to get temperature value
    SPI.transfer(0x20); //send second byte of command to get temperature value
    delay(35); //wait for conversion end
    SPI.setDataMode(SPI_MODE1); //change mode in order to listen
    tempMSB = SPI.transfer(0x00); //send dummy byte to read first byte of value
    tempMSB = tempMSB << 8; //shift first byte
    tempLSB = SPI.transfer(0x00); //send dummy byte to read second byte of value
    rawTemp = tempMSB | tempLSB; //combine first and second byte of value
    //Serial.print("Temperature raw =");
    //Serial.println(rawTemp);

    resetSensor();//resets the sensor

    return rawTemp;
};

int SensorClass::getRawPress() {
    /*
    Return the raw pressure value
    */
    
    unsigned int presMSB = 0; //first byte of value
    unsigned int presLSB =0; //last byte of value
    int rawPress = 0;
    SPI.transfer(0x0F); //send first byte of command to get pressure value
    SPI.transfer(0x40); //send second byte of command to get pressure value
    delay(35); //wait for conversion end
    SPI.setDataMode(SPI_MODE1); //change mode in order to listen
    presMSB = SPI.transfer(0x00); //send dummy byte to read first byte of value
    presMSB = presMSB << 8; //shift first byte
    presLSB = SPI.transfer(0x00); //send dummy byte to read second byte of value
    rawPress = presMSB | presLSB; //combine first and second byte of value
    //Serial.print("Pressure raw =");
    //Serial.println(rawPress);

    resetSensor();//resets the sensor

    return rawPress;
};

void SensorClass::updateSensor() {
    setCalibrationWords();
    setCalibrationFactors();
   // Serial.println("-----ALL SENSOR DATA-----");
   // Serial.print("Calibration Word #1: ");
   // Serial.println(calibrationWordOne);
   // Serial.print("Calibration Word #2: ");
   // Serial.println(calibrationWordTwo);
   // Serial.print("Calibration Word #3: ");
   // Serial.println(calibrationWordThree);
   // Serial.print("Calibration Word #4: ");
   // Serial.println(calibrationWordFour);
   // Serial.print("Calibration Factor #1: ");
   // Serial.println(calibrationFactorOne);
   // Serial.print("Calibration Factor #2: ");
   // Serial.println(calibrationFactorTwo);
   // Serial.print("Calibration Factor #3: ");
   // Serial.println(calibrationFactorThree);
   // Serial.print("Calibration Factor #4: ");
   // Serial.println(calibrationFactorFour);
   // Serial.print("Calibration Factor #5: ");
   // Serial.println(calibrationFactorFive);
   // Serial.print("Calibration Factor #6: ");
   // Serial.println(calibrationFactorSix);
    rawTemp = getRawTemp();
    rawPress = getRawPress();
};

float SensorClass::getRealTemp(int rawTempVal) {
    Serial.print("Calibration Factor 6 =");
    Serial.println(calibrationFactorSix);
    const long UT1 = (calibrationFactorFive << 3) + 10000;
    const long dT = rawTempVal - UT1;
    const long TEMP = 200 + ((dT * (calibrationFactorSix + 100)) >> 11);
    float realTemp = TEMP/10;

    return realTemp;
};

float SensorClass::getRealPress(int rawPressVal, int rawTempVal) {
    //Serial.print("Press raw val =");
    //Serial.println(rawPressVal);
    //Serial.print("Temp raw val =");
    //Serial.println(rawTempVal);
    const long UT1 = (calibrationFactorFive << 3) + 10000;
    const long dT = rawTempVal - UT1;
    const long OFF  = calibrationFactorTwo + (((calibrationFactorFour - 250) * dT) >> 12) + 10000;
    const long SENS = (calibrationFactorOne/2) + (((calibrationFactorThree + 200) * dT) >> 13) + 3000;
    long compedPress = (SENS * (rawPressVal - OFF) >> 12) + 1000;

    return compedPress;
    
};

float SensorClass::getTemp() {
    float temp = getRealTemp(rawTemp);
    return temp;
};

float SensorClass::getPress() {
    float press = getRealPress(rawPress, rawTemp);
    return press;
};

void SensorClass::printData(){
    Serial.println("-----ALL SENSOR DATA-----");
    Serial.print("Calibration Word #1: ");
    Serial.println(calibrationWordOne);
    Serial.print("Calibration Word #2: ");
    Serial.println(calibrationWordTwo);
    Serial.print("Calibration Word #3: ");
    Serial.println(calibrationWordThree);
    Serial.print("Calibration Word #4: ");
    Serial.println(calibrationWordFour);
    Serial.print("Calibration Factor #1: ");
    Serial.println(calibrationFactorOne);
    Serial.print("Calibration Factor #2: ");
    Serial.println(calibrationFactorTwo);
    Serial.print("Calibration Factor #3: ");
    Serial.println(calibrationFactorThree);
    Serial.print("Calibration Factor #4: ");
    Serial.println(calibrationFactorFour);
    Serial.print("Calibration Factor #5: ");
    Serial.println(calibrationFactorFive);
    Serial.print("Calibration Factor #6: ");
    Serial.println(calibrationFactorSix);
    Serial.println("");
    Serial.print("Raw Temp: ");
    Serial.println(rawTemp);
    Serial.print("Raw Press: ");
    Serial.println(rawPress);
};
