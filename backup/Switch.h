/*
 Switch.h - Library for the AMUP Button Pad.
 Created by Julio Terra, June 4, 2011.
 */

#ifndef Switch_h
#define Switch_h

#include "WProgram.h"
#include "AMUPconfig.h"
#include "InputElement.h"

class Switch: public InputElement {
    public:
        // general constants
        #define DIGITAL_SWITCH_DEBOUNCE   100   // interval of time that new input will be ignored via digital sensors
        #define DIGITAL_PREVIOUS_DEBOUNCE 50       // interval of time that new input will be ignored via digital sensors

        // switch states
        #define OFF            0   
        #define ON             1

        // holds whether the signal is inverted (e.g. LOW switch state is equal to switch ON or HIGH)
        bool is_inverted;
        bool is_momentary;

        // variables that manage switch state
        int previous_state;          // holds the current momentary state of the switch (on, off, or analog number)
        long last_state_switch;       // holds last time the switch state was changed
        long last_read_previous_state; // holds the last time the current state was recorded
    
        Switch(int, int);
        void invert_switch(bool);
        bool available();
};

#endif