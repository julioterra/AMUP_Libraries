/*
 RGBButtonTLC.h - Library for the AMUP Button Pad.
 Created by Julio Terra, June 4, 2011.
 */

#ifndef RGBButtonTLC_h
#define RGBButtonTLC_h

#include "WProgram.h"
#include "RGBButton.h"
#include "AMUPconfig.h"
    
class RGBButtonTLC: public RGBButton {    
    public:    
        RGBButtonTLC(int, int, int);
        void set_led_pins(int, int, int);
        void update_leds();
};

#endif