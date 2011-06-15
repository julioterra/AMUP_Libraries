/*
 RotaryEncoder.h - Library for reading a Rotary Encoder.
 Created by Julio Terra, June 2, 2011.
 */

#ifndef RotaryEncoder_h
#define RotaryEncoder_h

#include "WProgram.h"
#include "AMUPconfig.h"

class RotaryEncoder {
    private: 
        int pinA;
        int pinB;
        int interruptPin;
        bool new_data;
        
    public:
        int ID;
        int direction;
        volatile int encoderPos;
        volatile int encoderPosPrevious;
        int device_ID;
    
        RotaryEncoder(int,int, int, int);         // RotaryEncoder library constructor, accepts the number of encoder pins A and B, and the interrupt pin
        int get_interrupt_pin();
        void set_direction(int);
        void event();                     // RotaryEncoder library method that should be called by the interrupt call back function 
        bool available();
        int get_state();
        int get_print_state();
};

#endif