/*
 AnalogSwitch.h - Library for the AMUP Button Pad.
 Created by Julio Terra, June 4, 2011.
 */

#ifndef AnalogSwitch_h
#define AnalogSwitch_h

#include "WProgram.h"

class AnalogSwitch {
    public:
        // switch types
        #define OUTPUT_ANALOG_RANGE       127     
        #define AVG_READINGS              10
        #define STATE_CHANGE_THRESH       8
        #define DIGITAL_SWITCH_DEBOUNCE   100   // interval of time that new input will be ignored via digital sensors
        #define DIGITAL_PREVIOUS_DEBOUNCE 70   // interval of time that new input will be ignored via digital sensors

        // pin variables
        int pin;                 // holds the arduino pin where the switch data can be read

        // debug variables
        int debug_code;                 // holds the arduino pin where the switch data can be read

        // variables for object ID and types
        int ID;                  // holds identifier for the switch can be used as mux number for this switch

        // variables that manage switch state
        bool newState;            // holds whether the switch has changed state since last data read/get
        int lastStateSwitch;      // holds last time the switch state was changed
        int lastReadPreviousState;
        int currentState;         // holds new state of switch, that is compared to current state to determine if changes occured
        int previousState;        // holds the current momentary state of the switch (on, off, or analog number)

        // variables that define and manage analog range
        int analogRangeMin;      // holds the bottom of the range of an analog sensor
        int analogRangeMax;      // holds the top of the range of an analog sensor
        int analogRange;         // holds the size of the range of an analog sensor
        int adjustedAnalogState; // holds the analog state adjusted by the analog range 

        AnalogSwitch(int, int);
        void setAnalogRange(int, int);
        bool hasStateChanged();
        int getState();
        int getMessage();
        void debugToggle();

};

#endif