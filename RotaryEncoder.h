/*
 RotaryEncoder.h - Library for reading a Rotary Encoder.
 Created by Julio Terra, June 2, 2011.
 */

#ifndef RotaryEncoder_h
#define RotaryEncoder_h

#include "WProgram.h"
#include "AMUPconfig.h"
#include "InputElement.h"

class RotaryEncoder: public InputElement {
    private: 
//        int pin_a;
        int pin_b;
        int interrupt_pin;
//        bool new_data;
        
    public:
//        int ID;
        int direction;
        volatile int encoderPos;
//        volatile int output_state;
//        int device_ID;
    
        RotaryEncoder(int, int, int);   // RotaryEncoder library constructor, accepts the number of encoder pins A and B, and the interrupt pin
        int get_interrupt_pin();        // returns the appropriate interrupt pin number for pin_a of the encoder
        void set_direction(int);        // enables changing of direction based on whether you enter a number that is greater or smaller than 0
        void event();                   // method that should be called by the interrupt call back function 
        bool available();               // returns whether the state of the encoder has changed
//        float get_state();              // returns the actual state of the encoder
//        float get_print_state();        // 
};

#endif