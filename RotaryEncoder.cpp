#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder(int _ID, int _pin_a, int _pin_b) : InputElement(_ID, _pin_a) {
    pin_b = _pin_b;
    pinMode(pin_b, INPUT); 

    digitalWrite(pin, HIGH);         // turn on pullup resistor
    digitalWrite(pin_b, HIGH);       // turn on pullup resistor

    encoderPos = 0;
    new_state = false;
    direction = 1;
    
    if (pin == 2) interrupt_pin = 0;
    if (pin == 3) interrupt_pin = 1;
    if (pin == 18) interrupt_pin = 5;
    if (pin == 19) interrupt_pin = 4;
    if (pin == 20) interrupt_pin = 3;
    if (pin == 21) interrupt_pin = 2;
    else interrupt_pin -1;

}

int RotaryEncoder::get_interrupt_pin() {
    return interrupt_pin;
}

void RotaryEncoder::set_direction(int _direction) {
    if (_direction < 0) direction = -1;
    else direction = 1;
}

void RotaryEncoder::event() {
    if (digitalRead(pin) == digitalRead(pin_b)) encoderPos = 1 * direction;
    else encoderPos = -1 * direction;
    new_state = true;    
}

bool RotaryEncoder::available(){
    if (new_state) {
        output_state = encoderPos;
        encoderPos = 0;         
    }
    return new_state;     
}