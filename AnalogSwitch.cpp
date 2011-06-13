#include "WProgram.h"
#include "AnalogSwitch.h"


// CONSTRUCTOR: initializes an instance of the AnalogSwitch class
// PARAMS: an id number for the switch and the input pin number
AnalogSwitch::AnalogSwitch(int _ID, int _pin) {
    ID = _ID;
    pin = _pin;  
    pinMode(pin, INPUT);
    
    // initialize all variables
    newState = false;
    lastStateSwitch = 0;
    currentState = 0;
    previousState = 0;
    analogRangeMin = 0;
    analogRangeMax = 1023;
    analogRange = analogRangeMax - analogRangeMin;
    adjustedAnalogState = 0;

//    if (debug_code) {
//        Serial.print("ID ");   
//        Serial.print(ID);   
//        Serial.print(": AnalogSwitch(), switch pin: ");   
//        Serial.print(pin);   
//    }

}

// SET ANALOG: sets a custom range for the current instance of the switch. Standard range is from 0 to 1023.
// PARAMS: the max and minimum values of the analog range
void AnalogSwitch::setAnalogRange(int _min, int _max) {
    analogRangeMin = _min;      
    analogRangeMax = _max;   
    analogRange = analogRangeMax - analogRangeMin;      
    
//    if (debug_code) {
//        Serial.print("ID ");   
//        Serial.print(ID);   
//        Serial.print(": setAnalog(), range min: ");   
//        Serial.print(analogRangeMin);   
//        Serial.print(" range max: ");   
//        Serial.print(analogRangeMin);   
//        Serial.print(" range: ");   
//        Serial.println(analogRange);   
//    }
    
}

// HAS STATE CHANGED: reads switch pin and determines if state has changed
// RETURNS: true if switch state has changed, false if state has not changed
// if reading from mux, you need to set the proper pins first, outside of the library
bool AnalogSwitch::hasStateChanged() {
    long currentTime = millis();    
    int rawState = analogRead(pin);
    currentState = ((currentState * (AVG_READINGS -1)) + rawState)/AVG_READINGS;

    // calculate an average here
    
    if (currentState > (previousState + STATE_CHANGE_THRESH) || currentState < (previousState - STATE_CHANGE_THRESH)) {
        newState = true;
        previousState = currentState;
        if (analogRange == OUTPUT_ANALOG_RANGE) adjustedAnalogState = currentState;
        else adjustedAnalogState = int(float(float((currentState) - analogRangeMin)/float(analogRange)) * float(OUTPUT_ANALOG_RANGE));

//        if (debug_code) {
//            Serial.print("ID ");   
//            Serial.print(ID);   
//            Serial.print(": hasStateChanged(), analog raw: ");   
//            Serial.print(currentState);   
//            Serial.print(", adjusted val : ");   
//            Serial.println(adjustedAnalogState);   
//        }

        return true;   
    }
    return false;
}

// HAS STATE CHANGED: reads switch pin and determines if state has changed
// RETURNS: true if switch state has changed, false if state has not changed
int AnalogSwitch::getState() {
    if (newState) newState = false;
    
//    if (debug_code) {
//        Serial.print("ID ");   
//        Serial.print(ID);   
//        Serial.print(": getState(), led state updated, message passed: ");   
//        Serial.println(adjustedAnalogState);   
//    }

    return adjustedAnalogState;
}

// DEBUG TOGGLE: turns the debugging on and off, this prints a lot information to the serial port
// PARAMS RETURNS: n/a
void AnalogSwitch::debugToggle() {
    if (debug_code) debug_code = false;
    else debug_code = true;

//    if (debug_code) {
//        Serial.print("ID ");   
//        Serial.print(ID);   
//        Serial.print(": debugToggle(), debug status is: ");   
//        Serial.println(debug_code);   
//    }
}
