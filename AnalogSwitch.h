/*
 AMUP Input Element Libraries, Analog Switch
 Created by Julio Terra, June 4, 2011.
 
 This is the analog switch library from the AMUP Input Element set. This 
 library handles analog switches such as potentiometers and other 
 variable resistors.
 
 Hierarchy:
 - Parents: Input Element
 - Children: n/a 
 
 File name: AnalogSwitch.h 
 */

#ifndef AnalogSwitch_h
#define AnalogSwitch_h

#include "WProgram.h"
#include "AMUPconfig.h"
#include "InputElement.h"

class AnalogSwitch: public InputElement {
    public:
        // range and averaging variables
        #define OUTPUT_RANGE            127     
        #define AVG_READINGS            10
        #define STATE_CHANGE_THRESH     8

        // variables that manage switch state
        int last_reading;        // holds the current momentary state of the switch (on, off, or analog number)

        // variables that define and manage analog range
        int range_min;      // holds the bottom of the range of an analog sensor
        int range_max;      // holds the top of the range of an analog sensor
        int range;          // holds the size of the range of an analog sensor

        AnalogSwitch(int, int);             // constructor
        void set_analog_range(int, int);    // set range for analog switch
        bool available();                   // redefine the avaiable method

};

#endif