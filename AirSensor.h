/*
 AirSensor.h - Library for the AMUP Air Sensor.
 Created by Julio Terra, June 2, 2011.
 */

#ifndef AirSensor_h
#define AirSensor_h

#include "WProgram.h"
#include "AMUPconfig.h"

class AirSensor {
    private: 
        #define PRE_READING_BUFFER_SIZE      20  
        #define READINGS_ARRAY_SIZE          10
        #define TREND_RECOGNITION_MIN        4      
        #define TREND_NOISE_THRESHOLD        4      
        #define TIME_INTERVAL                15

        #define SENSOR_MIN                   125
        #define SENSOR_MAX                   480

        #define gestOnOff_SequenceTime       300
        #define gestOnOff_FullDelta          170
        #define gestOnOff_GradientDelta      100
        #define gestOnOff_PauseInterval      450
        #define gestUpDown_Bandwidth         30
        #define gestUpDown_IgnoreRange       70

        #define UP                           0
        #define DOWN                         1
        #define STOPPED                     -1
        #define GEST_ON                      1
        #define GEST_OFF                     0
        
        int mainPin;
        int sensorRange;
        
        // hand sensing variables
        boolean dataAvailable;
        boolean handActive;
        boolean handStatusChange;
        int handIntentionPrevious;
        
        // On/Off Gesture
        unsigned long gestOnOff_LastTime;
        boolean gestOn;
        boolean gestOff;
        
        // GEST_UP/Down Gesture
        int gestUpDown_Center;
    
        void moveUpOrDown();
        boolean turnOnOrOff();
        float gestOnOff();
        float gestUpDown();

    public:
        // data capture and processing variables
        unsigned long lastReading;
        int rawReading;
        int rawReadings[READINGS_ARRAY_SIZE];
        int preBuffer[PRE_READING_BUFFER_SIZE];
        int newReading;
        int handIntention;

        int volumeRange;
        float currentState;
        
        AirSensor(int);
        void setProximityPin(int);
        void reset();
        void addNewReading();
        void updateState();
        bool hasStateChanged();
        float getState();
        void printState(); 
        void printRawReadings();
};

#endif