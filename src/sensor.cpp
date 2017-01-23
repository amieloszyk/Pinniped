

#include "sensor.h"

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

    SPI.begin(); //see SPI library details on arduino.cc for details
    SPI.setBitOrder(MSBFIRST);
    SPI.setClockDivider(SPI_CLOCK_DIV32); //divide 16 MHz to communicate on 500 kHz
    pinMode(clock, OUTPUT);
};

void SensorClass::setCalibrationWords() {
    /*
    Get the calibration words
    */

    TCCR1B = (TCCR1B & 0xF8) | 1 ; //generates the MCKL signal
    analogWrite (clock, 128) ; 

    resetSensor();//resets the sensor - caution: afterwards mode = SPI_MODE0!

    //Calibration word 1
    unsigned int calibrationWordOne = 0;
    unsigned int inbyte1 = 0;
    SPI.transfer(0x1D); //send first byte of command to get calibration word 1
    SPI.transfer(0x50); //send second byte of command to get calibration word 1
    SPI.setDataMode(SPI_MODE1); //change mode in order to listen
    calibrationWordOne = SPI.transfer(0x00); //send dummy byte to read first byte of word
    calibrationWordOne = calibrationWordOne << 8; //shift returned byte 
    inbyte1 = SPI.transfer(0x00); //send dummy byte to read second byte of word
    calibrationWordOne = calibrationWordOne | inbyte1; //combine first and second byte of word
    //Serial.print("Calibration word 1 =");
    //Serial.println(result1);

    resetSensor();//resets the sensor

    //Calibration word 2; see comments on calibration word 1
    unsigned int calibrationWordTwo = 0;
    byte inbyte2 = 0; 
    SPI.transfer(0x1D);
    SPI.transfer(0x60);
    SPI.setDataMode(SPI_MODE1); 
    calibrationWordTwo = SPI.transfer(0x00);
    calibrationWordTwo = calibrationWordTwo <<8;
    inbyte2 = SPI.transfer(0x00);
    calibrationWordTwo = calibrationWordTwo | inbyte2;
    //Serial.print("Calibration word 2 =");
    //Serial.println(result2);  

    resetSensor();//resets the sensor

    //Calibration word 3; see comments on calibration word 1
    unsigned int calibrationWordThree = 0;
    byte inbyte3 = 0;
    SPI.transfer(0x1D);
    SPI.transfer(0x90); 
    SPI.setDataMode(SPI_MODE1); 
    calibrationWordThree = SPI.transfer(0x00);
    calibrationWordThree = calibrationWordThree <<8;
    inbyte3 = SPI.transfer(0x00);
    calibrationWordThree = calibrationWordThree | inbyte3;
    //Serial.print("Calibration word 3 =");
    //Serial.println(result3);  

    resetSensor();//resets the sensor

    //Calibration word 4; see comments on calibration word 1
    unsigned int calibrationWordFour = 0;
    byte inbyte4 = 0;
    SPI.transfer(0x1D);
    SPI.transfer(0xA0);
    SPI.setDataMode(SPI_MODE1); 
    calibrationWordFour = SPI.transfer(0x00);
    calibrationWordFour = calibrationWordFour <<8;
    inbyte4 = SPI.transfer(0x00);
    calibrationWordFour = calibrationWordFour | inbyte4;
    //Serial.print("Calibration word 4 =");
    //Serial.println(result4);

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

    //Serial.println(c1);
    //Serial.println(c2);
    //Serial.println(c3);
    //Serial.println(c4);
    //Serial.println(c5);
    //Serial.println(c6);

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
    //Serial.println(D2); //voilá!

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
    Serial.print("Pressure raw =");
    Serial.println(D1);

    resetSensor();//resets the sensor

    return rawPress;
};
