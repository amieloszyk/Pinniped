/*
This class handles interactions with the MS5541 sensor. It measures 
pressure and temperature.

@author: Alexander J. Mieloszyk (amieloszyk)
Created on January 21st, 2017
*/

#include <SPI.h>

class SensorClass{

    protected:

        const int clockPin = 9;

        int calibrationWordOne;
        int calibrationWordTwo;
        int calibrationWordThree;
        int calibrationWordFour;

        long calibrationFactorOne;
        long calibrationFactorTwo;
        long calibrationFactorThree;
        long calibrationFactorFour;
        long calibrationFactorFive;
        long calibrationFactorSix;

        void resetSensor();
        void setCalibrationWords();
        void setCalibrationFactors();
        int getRawTemp();
        int getRawPress();

        float getRealTemp(int rawTemp);
        float getRealPress(int rawPress);

    public:

        void setupSensor();
        void updateSensor();
        float getTemp();
        float getPress();

}