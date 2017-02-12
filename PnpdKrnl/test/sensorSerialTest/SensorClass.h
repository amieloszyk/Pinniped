/*
This class handles interactions with the MS5541 sensor. It measures 
pressure and temperature.

@author: Alexander J. Mieloszyk (amieloszyk)
Created on January 21st, 2017
*/

class SensorClass{

    protected:

        int clockPin;

        unsigned int calibrationWordOne;
        unsigned int calibrationWordTwo;
        unsigned int calibrationWordThree;
        unsigned int calibrationWordFour;

        long calibrationFactorOne;
        long calibrationFactorTwo;
        long calibrationFactorThree;
        long calibrationFactorFour;
        long calibrationFactorFive;
        long calibrationFactorSix;

        int rawTemp;
        int rawPress;

        void resetSensor();
        void setCalibrationWords();
        void setCalibrationFactors();
        int getRawTemp();
        int getRawPress();

        float getRealTemp(int rawTempVal);
        float getRealPress(int rawPressVal, int rawTempVal);

    public:

        SensorClass();
        void setupSensor();
        void updateSensor();
        float getTemp();
        float getPress();
        void printData();

};
