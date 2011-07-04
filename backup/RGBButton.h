/*
 RGBButton.h - Library for the AMUP Button Pad.
 Created by Julio Terra, June 4, 2011.
 */

#ifndef RGBButton_h
#define RGBButton_h

#include "WProgram.h"
#include "Switch.h"
#include "AMUPconfig.h"

class RGBButton: public Switch {
    
    public:    
        int led_pins[RGB_COUNT];
        int max_bright;
        int toggle_states;         // holds number of toggle states for a given switch has, supports up to 6 toggle on states
        int led_digital_states[TOGGLE_MAX][RGB_COUNT];  // holds brightness of each led associted to toggle states(from 0 to 4056) 
    
        bool led_on;
        bool led_available;            
        int current_led_state[RGB_COUNT];    

        RGBButton(int, int, int);
        virtual void set_led_pins(int, int, int, int) {};
        virtual void set_led_pins(int, int, int) {};
        bool set_led_state(int, int, int, int);
        bool available();
        void turn_on_leds(int, int, int);
        void turn_on_leds();
        void turn_off_leds();
        void set_current_led_state(int);
        void momentary_button(bool);
    
        virtual void update_leds() {};
};

#endif