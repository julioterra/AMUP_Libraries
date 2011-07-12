#include "WProgram.h"
#include "Switch.h"


// CONSTRUCTOR: initializes an instance of the switch class
// PARAMS: an id number for the switch and the input pin number
Switch::Switch(int _ID, int _pin) : InputElement(_ID, _pin) {
    new_state = false;
    current_state = 0;
    previous_state = 0;
    last_state_switch = 0;
    last_read_previous_state = 0;
    is_inverted = false;
    is_momentary = true;

}

// HAS STATE CHANGED: reads switch pin and determines if state has changed
// RETURNS: true if switch state has changed, false if state has not changed
// if reading from mux, you need to set the proper pins first, outside of the library
void Switch::invert_switch(bool _onState) {
    if (_onState) { 
        is_inverted = true;    
        digitalWrite(pin, HIGH);
    }
    
    else {
        is_inverted = false;   
        digitalWrite(pin, LOW);
    }
    
}

// HAS STATE CHANGED: reads switch pin and determines if state has changed
// RETURNS: true if switch state has changed, false if state has not changed
// if reading from mux, you need to set the proper pins first, outside of the library
bool Switch::available() {
    current_state = digitalRead(pin);
    
    if (is_inverted) {
        if (current_state == LOW) current_state = HIGH;
        else current_state = LOW;        
    }

    if (current_state == previous_state) last_read_previous_state = millis();
    else if (current_state != previous_state) {
        if(((millis() - last_state_switch) > DIGITAL_SWITCH_DEBOUNCE) || ((millis() - last_read_previous_state) > DIGITAL_PREVIOUS_DEBOUNCE)) {
            new_state = true;
            last_state_switch = millis();
            previous_state = current_state;
            if (is_momentary) output_state = current_state;

            return true;   
        }
    }
    return false;
}