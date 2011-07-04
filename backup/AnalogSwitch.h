/*
 AnalogSwitch.h - Library for the AMUP Button Pad.
 Created by Julio Terra, June 4, 2011.
 */

#ifndef AnalogSwitch_h
#define AnalogSwitch_h

#include "WProgram.h"
#include "AMUPconfig.h"
#include "InputElement.h"

class AnalogSwitch: public InputElement {
    public:
        // switch types
        #define OUTPUT_RANGE            127     
        #define AVG_READINGS            10
        #define STATE_CHANGE_THRESH     8

        // variables that manage switch state
        int previous_state;        // holds the current momentary state of the switch (on, off, or analog number)

        // variables that define and manage analog range
        int range_min;      // holds the bottom of the range of an analog sensor
        int range_max;      // holds the top of the range of an analog sensor
        int range;         // holds the size of the range of an analog sensor

        AnalogSwitch(int, int);
        void set_analog_range(int, int);
        bool available();

};

#endif