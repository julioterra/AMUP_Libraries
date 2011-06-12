#include "WProgram.h"
#include "RGBButton.h"
#include <Tlc5940.h>


// CONSTRUCTOR: initializes an instance of the switch class
// PARAMS: an id number for the switch and the input pin number and number of states
RGBButton::RGBButton(int _ID, int _pin, int _states) {
    ID = _ID;
    pin = _pin;  
    if (_states >= 2 && _states <= TOGGLE_MAX) toggleStates = _states;
    else toggleStates = 2;
    
    // initialize all variables
    ledPins[R] = 0;
    ledPins[G] = 0;
    ledPins[B] = 0;
    LEDavailable = false;
    
    newState = false;
    lastStateSwitch = 0;
    currentState = 0;
    previousState = 0;
    currentToggleState = 0;  
    for (int i = 0; i < TOGGLE_MAX; i++) 
        for (int j = 0; j < LED_COUNT; j++) ledDigitalStates[i][j] = 0;

//    if (debug_code) {
//        Serial.print("ID ");   
//        Serial.print(ID);   
//        Serial.print(": RGBButton(), switch pin: ");   
//        Serial.print(pin);   
//        Serial.print(", toggle states: ");   
//        Serial.print(toggleStates);   
//    }

}

void RGBButton::setLEDpins(int _R, int _G, int _B) {    
    ledPins[R] = _R;
    ledPins[G] = _G;
    ledPins[B] = _B;
    LEDavailable = true;
    
//    if (debug_code) {
//        Serial.print("ID ");   
//        Serial.print(ID);   
//        Serial.print(": setLEDpins(), RGB: ");   
//        Serial.print(ledPins[R]);   
//        Serial.print(", ");   
//        Serial.print(ledPins[G]);   
//        Serial.print(", ");   
//        Serial.print(ledPins[B]);   
//    }
}

// SET DIGITAL LED STATE: sets the led state associated with each digital pin state
// PARAMS: a digital switch state and the associated R, G, and B led state
// RETURNS: true if switch is set to digital, and the switch features the appropriate number of toggle states
bool RGBButton::setDigitalLEDState(int _state, int _R, int _G, int _B) {
    if (_state >= TOGGLE_MAX) _state = TOGGLE_MAX - 1;
    else if (_state < 0) _state = 0;
    ledDigitalStates[_state][R] = constrain(_R, -1, MAX_BRIGHT);
    ledDigitalStates[_state][G] = constrain(_G, -1, MAX_BRIGHT);
    ledDigitalStates[_state][B] = constrain(_B, -1, MAX_BRIGHT);
    
//    if (debug_code) {
//        Serial.print("ID ");   
//        Serial.print(ID);   
//        Serial.print(": setDigitalLEDState(), set state: ");   
//        Serial.println(_state);   
//        Serial.print(", set RGB: ");   
//        Serial.print(ledDigitalStates[_state][R]);   
//        Serial.print(", ");   
//        Serial.print(ledDigitalStates[_state][G]);   
//        Serial.print(", ");   
//        Serial.println(ledDigitalStates[_state][B]);   
//    }
    
//    if (type == DIGITAL && _state < toggleStates && LEDavailable) return true;
    if (_state < toggleStates && LEDavailable) return true;
    else return false;
}

// HAS STATE CHANGED: reads switch pin and determines if state has changed
// RETURNS: true if switch state has changed, false if state has not changed
// if reading from mux, you need to set the proper pins first, outside of the library
bool RGBButton::hasStateChanged() {
    long currentTime = millis();

    currentState = digitalRead(pin);

    if (currentState == previousState) lastReadPreviousState = currentTime;
    else if (currentState != previousState) {
        if(((currentTime - lastStateSwitch) > DIGITAL_SWITCH_DEBOUNCE) || ((currentTime - lastReadPreviousState) > DIGITAL_PREVIOUS_DEBOUNCE)) {
            lastStateSwitch = currentTime;
            previousState = currentState;   
            if (currentState == ON) {
                newState = true;
                currentToggleState++;
                if (currentToggleState >= toggleStates) currentToggleState = 0;
            }
        }

        /** FOR MOMENTARY SWITCHES
         * if(((currentTime - lastStateSwitch) > DIGITAL_SWITCH_DEBOUNCE) || ((currentTime - lastReadPreviousState) > DIGITAL_PREVIOUS_DEBOUNCE)) {
         *    newState = true;
         *    lastStateSwitch = currentTime;
         *    previousState = currentState;   
         *    currentToggleState = currentState;
         * }
         **/
        
    }

    //            if (debug_code) {
    //                Serial.print(" ID ");   
    //                Serial.print(ID);   
    //                if (newState) Serial.print(": hasStateChanged(), toggle state has changed to: ");   
    //                else Serial.print(": hasStateChanged(), toggle state has remained at: ");   
    //                Serial.println(currentToggleState);   
    //            }

    if (newState) return true;
    return false;
}

// HAS STATE CHANGED: reads switch pin and determines if state has changed
// RETURNS: true if switch state has changed, false if state has not changed
int RGBButton::getState() {
    updateLEDs();

//        if (debug_code) {
//            Serial.print("ID ");   
//            Serial.print(ID);   
//            Serial.print(": getState(), led state updated, message passed: ");   
//            Serial.println(currentToggleState);   
//        }

    if (newState) newState = false;
    return currentToggleState;
}

// UPDATE LEDS: updates the state of the LEDs for this switch, based on the state of the switch
// PARAMS & RETURNS: N/A
void RGBButton::updateLEDs() {
    if (LEDavailable) {

//        if (debug_code) {
//            Serial.print("ID ");   
//            Serial.print(ID);   
//            Serial.print(": updateLEDs(), Rval : ");   
//            Serial.print(ledDigitalStates[currentToggleState][R]);   
//            Serial.print(", Gval : ");   
//            Serial.print(ledDigitalStates[currentToggleState][G]);   
//            Serial.print(", Bval : ");   
//            Serial.println(ledDigitalStates[currentToggleState][B]);   
//        }
        
        if (newState) {
            turnOnLEDs();
        }
    }
}

// TURN ON LEDS: turns on the leds. activates their current toggle state
// NOTES: you must follow a call to this function with a call to the Tlc.update() function for updates to take effect
// PARAMS & RETURNS: N/A
void RGBButton::turnOnLEDs() {
    Tlc.set(ledPins[R], ledDigitalStates[currentToggleState][R]);
    Tlc.set(ledPins[G], ledDigitalStates[currentToggleState][G]);
    Tlc.set(ledPins[B], ledDigitalStates[currentToggleState][B]);
}

// TURN ON LEDS: turns on the leds. activates the color passed in parameters.
// NOTES: you must follow a call to this function with a call to the Tlc.update() function for updates to take effect
// PARAMS: three integers, one for each color
void RGBButton::turnOnLEDs(int _r, int _g, int _b) {
    Tlc.set(ledPins[R], constrain(_r,0,MAX_BRIGHT));
    Tlc.set(ledPins[G], constrain(_g,0,MAX_BRIGHT));
    Tlc.set(ledPins[B], constrain(_b,0,MAX_BRIGHT));
}

// TURN OFF LEDS: turns oFF the leds.
// NOTES: you must follow a call to this function with a call to the Tlc.update() function for updates to take effect
// PARAMS & RETURNS: N/A
void RGBButton::turnOffLEDs() {
    Tlc.set(ledPins[R], 0);
    Tlc.set(ledPins[G], 0);
    Tlc.set(ledPins[B], 0);
}


// DEBUG TOGGLE: turns the debugging on and off, this prints a lot information to the serial port
// PARAMS RETURNS: n/a
void RGBButton::debugToggle() {
    if (debug_code) debug_code = false;
    else debug_code = true;

//    if (debug_code) {
//        Serial.print("ID ");   
//        Serial.print(ID);   
//        Serial.print(": debugToggle(), debug status is: ");   
//        Serial.println(debug_code);   
//    }
}

