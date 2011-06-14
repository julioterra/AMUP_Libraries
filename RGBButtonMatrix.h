/*
 RGBButtonMatrix.h - Library for the AMUP Button Pad.
 Created by Julio Terra, June 4, 2011.
 */

#ifndef RGBButtonMatrix_h
#define RGBButtonMatrix_h

#include "WProgram.h"
#include "RGBButton.h"
#include "AMUPconfig.h"

class RGBButtonMatrix: public RGBButton {
    
    public:    
        RGBButtonMatrix(int, int, int);
        void set_led_pins(int, int, int, int);
        void update_leds();
};

#endif