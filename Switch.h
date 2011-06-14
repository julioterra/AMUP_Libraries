/*
 Switch.h - Library for the AMUP Button Pad.
 Created by Julio Terra, June 4, 2011.
 */

#ifndef Switch_h
#define Switch_h

#include "WProgram.h"
#include "AMUPconfig.h"

class Switch {
    public:
        // general constants
        #define DIGITAL_SWITCH_DEBOUNCE   100   // interval of time that new input will be ignored via digital sensors
        #define DIGITAL_PREVIOUS_DEBOUNCE 50       // interval of time that new input will be ignored via digital sensors

        // switch states
        #define OFF            0   
        #define ON             1

        // pin variables
        int pin;                 // holds the arduino pin where the switch data can be read

        // variables for object ID and toggle states
        int ID;                   // holds identifier for the switch can be used as mux number for this switch
    
        // holds whether the signal is inverted (e.g. LOW switch state is equal to switch ON or HIGH)
        bool is_inverted;
        bool is_momentary;

        // variables that manage switch state
        int current_state;           // holds new state of switch, that is compared to current state to determine if changes occured
        int previous_state;          // holds the current momentary state of the switch (on, off, or analog number)
        bool new_state;              // holds whether the switch has changed state since last data read/get
        long last_state_switch;       // holds last time the switch state was changed
        long last_read_previous_state; // holds the last time the current state was recorded
    
        Switch(int, int);
        void invert_switch(bool);
        bool available();
        int get_state();    
};

#endif