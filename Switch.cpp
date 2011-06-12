#include "WProgram.h"
#include "Switch.h"


// CONSTRUCTOR: initializes an instance of the switch class
// PARAMS: an id number for the switch and the input pin number
Switch::Switch(int _ID, int _pin) {
    ID = _ID;
    pin = _pin;  
    
    newState = false;
    currentState = 0;
    previousState = 0;
    lastStateSwitch = 0;
    lastReadPreviousState = 0;
    isInverted = false;

//    if (debug_code) {
//        Serial.print("ID ");   
//        Serial.print(ID);   
//        Serial.print(": Switch(), switch pin: ");   
//        Serial.print(pin);   
//    }

}

// HAS STATE CHANGED: reads switch pin and determines if state has changed
// RETURNS: true if switch state has changed, false if state has not changed
// if reading from mux, you need to set the proper pins first, outside of the library
void Switch::setPolarity(int _onState) {
    if (_onState <= 0) isInverted = true;
    else isInverted = false;
    
    //    if (debug_code) {
    //        Serial.print("ID ");   
    //        Serial.print(ID);   
    //        Serial.print(": setPolarity(), polarity: ");   
    //        Serial.print(constrain(_onState, -1, 2);   
    //    }

}

// HAS STATE CHANGED: reads switch pin and determines if state has changed
// RETURNS: true if switch state has changed, false if state has not changed
// if reading from mux, you need to set the proper pins first, outside of the library
bool Switch::hasStateChanged() {
//    long currentTime = millis();

    currentState = digitalRead(pin);

//    if (debug_code) {
//        Serial.print(millis());
//        Serial.print(" ID ");   
//        Serial.print(ID);   
//        Serial.print(": hasStateChanged(), digital momentary state: ");   
//        Serial.println(currentState);   
//    }
    
    if (currentState == previousState) lastReadPreviousState = millis();
    else if (currentState != previousState) {
        if(((millis() - lastStateSwitch) > DIGITAL_SWITCH_DEBOUNCE) || ((millis() - lastReadPreviousState) > DIGITAL_PREVIOUS_DEBOUNCE)) {
            newState = true;
            lastStateSwitch = millis();
            previousState = currentState;   
            
//            if (debug_code) {
//                Serial.print(millis());
//                Serial.print(" ID ");   
//                Serial.print(ID);   
//                Serial.print(": hasStateChanged(), switch state: ");   
//                Serial.println(currentState);   
//            }

            return true;   
        }
    }
    return false;
}



// HAS STATE CHANGED: reads switch pin and determines if state has changed
// RETURNS: true if switch state has changed, false if state has not changed
int Switch::getState() {
    if (newState) {
        newState = false;
    }

//    if (debug_code) {
//        Serial.print("ID ");   
//        Serial.print(ID);   
//        Serial.print(": getState(), led state updated, message passed: ");   
//        Serial.println(currentState);   
//    }

    return currentState;
}

// DEBUG TOGGLE: turns the debugging on and off, this prints a lot information to the serial port
// PARAMS RETURNS: n/a
void Switch::debugToggle() {
    if (debug_code) debug_code = false;
    else debug_code = true;

//    if (debug_code) {
//        Serial.print("ID ");   
//        Serial.print(ID);   
//        Serial.print(": debugToggle(), debug status is: ");   
//        Serial.println(debug_code);   
//    }
}

