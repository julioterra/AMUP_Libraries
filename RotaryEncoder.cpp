#include "WProgram.h"
#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder(int _ID, int _pinA, int _pinB) {
    pinA = _pinA;
    pinB = _pinB;
    pinMode(pinA, INPUT); 
    pinMode(pinB, INPUT); 
    ID = _ID;

    digitalWrite(pinA, HIGH);       // turn on pullup resistor
    digitalWrite(pinB, HIGH);       // turn on pullup resistor

    encoderPos = 0;
    new_data = false;
    debug_code = false;
    direction = 1;
    
    if (_pinA == 2) interruptPin = 0;
    if (_pinA == 3) interruptPin = 1;
    if (_pinA == 18) interruptPin = 5;
    if (_pinA == 19) interruptPin = 4;
    if (_pinA == 20) interruptPin = 3;
    if (_pinA == 21) interruptPin = 2;
    else interruptPin -1;
    
    if (debug_code){
        Serial.print("RotaryEncoder::RotaryEncoder() - pin A: ");
        Serial.print(pinA, DEC);
        Serial.print(", pin B: ");
        Serial.println(pinB, DEC);
        Serial.print(", pin B: ");
        Serial.println(encoderPos, DEC);
    }

}

int RotaryEncoder::get_interrupt_pin() {
    return interruptPin;
}

void RotaryEncoder::set_direction(int _direction) {
    if (_direction < 0) direction = -1;
    else direction = 1;
    
    if (debug_code){
        Serial.print("RotaryEncoder::set_direction() - direction: ");
        Serial.println(direction, DEC);
    }

}

void RotaryEncoder::event() {
    if (digitalRead(pinA) == digitalRead(pinB)) encoderPos = 1 * direction;
    else encoderPos = -1 * direction;
    new_data = true;    
    
    if (debug_code){
        Serial.print("RotaryEncoder::event() - encoder position: ");
        Serial.println(encoderPos, DEC);
    }
    
}

bool RotaryEncoder::available(){
    return new_data;     
}

int RotaryEncoder::get_state(){
    if (new_data) new_data = false;
    int return_val = encoderPos;
    encoderPos = 0; 

    if (debug_code){
        Serial.print("RotaryEncoder::get_data() - encoder position: ");
        Serial.println(return_val, DEC);
    }

    return return_val;
}




