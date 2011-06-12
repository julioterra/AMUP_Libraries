/*
 RGBButton.h - Library for the AMUP Button Pad.
 Created by Julio Terra, June 4, 2011.
 */

#ifndef RGBButton_h
#define RGBButton_h

#include "WProgram.h"

class RGBButton {
    public:
        // general constants
        #define TOGGLE_MAX     5
        #define DIGITAL_SWITCH_DEBOUNCE   90   // interval of time that new input will be ignored via digital sensors
        #define DIGITAL_PREVIOUS_DEBOUNCE 50       // interval of time that new input will be ignored via digital sensors
        #define MAX_BRIGHT     1000

        // switch states
        #define OFF            0   
        #define ON             1

        // led related constants
        #define R              0
        #define G              1
        #define B              2
        #define LED_COUNT      3   // holds the number of led pins associated to each light (set to three as default)

        // pin variables
        int pin;                 // holds the arduino pin where the switch data can be read
        int ledPins[LED_COUNT];  // holds the tlc5940 pin number for each led 

        // debug variables
        int debug_code;                 // holds the arduino pin where the switch data can be read

        // variables for object ID and toggle states
        int ID;                   // holds identifier for the switch can be used as mux number for this switch
        int toggleStates;         // holds number of toggle states for a given switch has, supports up to 6 toggle on states

        // variables that manage switch state
        int currentState;         // holds new state of switch, that is compared to current state to determine if changes occured
        int previousState;        // holds the current momentary state of the switch (on, off, or analog number)
        int currentToggleState;   // holds the current toggle state of a switch
        bool newState;            // holds whether the switch has changed state since last data read/get
        long lastStateSwitch;      // holds last time the switch state was changed
        long lastReadPreviousState;
    
        // variables used to manage led states
        bool LEDavailable;            // holds whether an LED is linked to this switch/switch
        int ledDigitalStates[TOGGLE_MAX][LED_COUNT];  // holds brightness of each led associted to toggle states(from 0 to 4056)

        RGBButton(int, int, int);
        void setLEDpins(int, int, int); 
        bool setDigitalLEDState(int, int, int, int);
        bool hasStateChanged();
        int getState();
        void updateLEDs();
        void turnOnLEDs();
        void turnOnLEDs(int, int, int);
        void turnOffLEDs();
        void debugToggle();
    
};

#endif