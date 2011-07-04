#include "AnalogSwitch.h"


// CONSTRUCTOR: initializes an instance of the AnalogSwitch class
// PARAMS: an id number for the switch and the input pin number
AnalogSwitch::AnalogSwitch(int _ID, int _pin) : InputElement(_ID, _pin) {
    new_state = false;
    current_state = 0;
    last_reading = 0;
    range_min = 0;
    range_max = 1023;
    range = range_max - range_min;
    output_state = 0;
}

// SET ANALOG: sets a custom range for the current instance of the switch. Standard range is from 0 to 1023.
// PARAMS: the max and minimum values of the analog range
void AnalogSwitch::set_analog_range(int _min, int _max) {
    range_min = _min;      
    range_max = _max;   
    range = range_max - range_min;      
}

// HAS STATE CHANGED: reads switch pin and determines if state has changed
// RETURNS: true if switch state has changed, false if state has not changed
// if reading from mux, you need to set the proper pins first, outside of the library
bool AnalogSwitch::available() {
    long currentTime = millis();    
    int rawState = analogRead(pin);

    // calculate a running average
    current_state = ((current_state * (AVG_READINGS -1)) + rawState)/AVG_READINGS;

    // check if the sensor readings have exceeded a threshold
    if (current_state > (last_reading + STATE_CHANGE_THRESH) || current_state < (last_reading - STATE_CHANGE_THRESH)) {
        new_state = true;
        last_reading = current_state;
        if (range == OUTPUT_RANGE) output_state = current_state;
        else output_state = int(float(float((current_state) - range_min)/float(range)) * float(OUTPUT_RANGE));
        return true;   
    }
    return false;
}