/*
 AirSensor.h - Library for the AMUP Air Sensor.
 Created by Julio Terra, June 2, 2011.
 */

#ifndef AirSensor_h
#define AirSensor_h

#include "WProgram.h"

class AirSensor {
    private: 
        #define PRE_READING_BUFFER_SIZE      20    // useful variable to tweak to improve performance of sensor  
        #define READINGS_ARRAY_SIZE          10
        #define TREND_RECOGNITION_MIN        4      
        #define TREND_NOISE_THRESHOLD        4      
        #define timer_interval               15

        #define SENSOR_MIN                   125
        #define SENSOR_MAX                   480
        #define TOP_VOLUME                   127
        #define VOLUME_MIN                   0

        #define sensor_ID                    16

        #define gestOnOff_SequenceTime       300
        #define gestOnOff_FullDelta          180
        #define gestOnOff_GradientDelta      100
        #define gestOnOff_PauseInterval      450
//    int gestUpDown_Bandwidth;
//    int gestUpDown_IgnoreRange;

        #define UP                           0
        #define DOWN                         1
        #define STOPPED                     -1
        #define GEST_ON                      1
        #define GEST_OFF                     0
        
//        HighpassFilter hp;
//        int filteredData;
//        int filteredDataPrevious;
        int mainPin;
        
        int sensorRange;
        int volumeRange;
        float masterVolume;
        boolean newData;
        
        // hand sensing variables
        boolean handActive;
        boolean handStatusChange;
        int handIntentionPrevious;
        
        // On/Off Gesture
        unsigned long gestOnOff_LastTime;
        boolean gestOn;
        boolean gestOff;
        
        // GEST_UP/Down Gesture
        int gestUpDown_Center;
//        int gestUpDown_Shift;
        int gestUpDown_Bandwidth;
        int gestUpDown_IgnoreRange;
        
        void volumeUpDownMIDI();
        boolean volumeOnOffMIDI();
        int gestOnOff();
        int gestUpDown();

        // void addNewTime(unsigned long);
        boolean recursiveCheck(int, int**, int**, int, int, int);
        
    public:
        // data capture and processing variables
        unsigned long lastReading;
        int rawReadings[READINGS_ARRAY_SIZE];
        int preBuffer[PRE_READING_BUFFER_SIZE];
        int rawReading;
        int newReading;
        int handIntention;
        
        AirSensor(int);
        void reset();
        void setProximityPin(int);
        void addNewReading();
        void updateVolumeMIDI();
//        void printMIDIVolume();
        int play();
        void printRawReadings();
};

#endif