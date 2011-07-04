#include "InputElement.h"


// CONSTRUCTOR: initializes an instance of the input element class
// PARAMS: an id number and input pin for each instance of an input element
InputElement::InputElement(int _ID, int _pin) {
    ID = _ID;
    pin = _pin;  
    pinMode(pin, INPUT);
    new_state = false;
    current_state = 0;
    output_state = 0;
}

float InputElement::get_state() {
    if (new_state) new_state = false;
    return output_state;
}

float InputElement::get_print_state() {
    Serial.println(int(output_state));
    return get_state();
}