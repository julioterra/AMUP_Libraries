/*
 InputElement.h - Library for the AMUP Button Pad.
 Created by Julio Terra, June 4, 2011.
 */

#ifndef InputElement_h
#define InputElement_h

#include "WProgram.h"
#include "AMUPconfig.h"

class InputElement {
    public:
        // pin variables
        int ID;                     // holds the id number for this input    
        int pin;                    // holds the arduino pin from where the input will be read

        bool new_state;
        float current_state;
        float output_state;

        InputElement(int, int);        // initializes all variables
        virtual bool available() {};   // placeholder function for the available function that will be defined in child classes
        float get_state();             // function that returns current_state and resets new_state flag
        float get_print_state();       // same as get_state function but also prints current_state to serial port
};

#endif