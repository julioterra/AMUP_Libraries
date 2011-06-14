#include "WProgram.h"
#include "RGBButton.h"


/********************************************** 
 * FUNCTION THAT NEEDS TO BE CUSTOMIZED BETWEEN MATRIX AND TLC APPROACHES
 **********************************************/
// CONSTRUCTOR: initializes an instance of the switch class
// PARAMS: an id number for the switch and the input pin number
RGBButton::RGBButton(int _ID, int _input_pin, int _states) : Switch(_ID, _input_pin) {
    toggle_states = _states;
    is_momentary = false;
    
    led_available = false;
    led_on = false;
    
    for (int j = 0; j < RGB_COUNT; j++) current_led_state[j] = 0;
    for (int i = 0; i < TOGGLE_MAX; i++) 
        for (int j = 0; j < RGB_COUNT; j++) led_digital_states[i][j] = 0;
}

/********************************************** 
 * VIRTUAL FUNCTION 
 */
void RGBButton::set_led_pins(int _LED_pin, int _R_pin, int _G_pin, int _B_pin) {
}

/********************************************** 
 * VIRTUAL FUNCTION 
 */
void RGBButton::set_led_pins(int _R_pin, int _G_pin, int _B_pin) {
}

bool RGBButton::set_led_state(int _state, int _R, int _G, int _B) {
    if (_state >= TOGGLE_MAX || _state < 0 || !led_available) return false;

    led_digital_states[_state][R] = constrain(_R, 0, 1);
    led_digital_states[_state][G] = constrain(_G, 0, 1);
    led_digital_states[_state][B] = constrain(_B, 0, 1);
    return true;
}

bool RGBButton::available() {    
    update_leds();
    if(Switch::available()) {
        if (is_momentary) {
            set_current_led_state(current_state);
            return true; 
        }
        else if (current_state == ON) {
            new_state = true;
            current_toggle_state++;
            if (current_toggle_state >= toggle_states) current_toggle_state = 0;
            set_current_led_state(current_toggle_state);
            return true;
        }
        else new_state = false;
    } 
    else return false;
}


void RGBButton::set_current_led_state(int _state) {
    current_led_state[R] = led_digital_states[_state][R];
    current_led_state[G] = led_digital_states[_state][G];
    current_led_state[B] = led_digital_states[_state][B];
}

// HAS STATE CHANGED: reads switch pin and determines if state has changed
// RETURNS: true if switch state has changed, false if state has not changed
int RGBButton::get_state() {
    if (new_state) new_state = false;
    return current_toggle_state;
}

void RGBButton::turn_on_leds() {
    led_on = true;
}

void RGBButton::turn_on_leds(int _R, int _G, int _B) {
    current_led_state[R] = constrain(_R, 0, 1);
    current_led_state[G] = constrain(_G, 0, 1);
    current_led_state[B] = constrain(_B, 0, 1);
    led_on = true;
}

void RGBButton::turn_off_leds() {
    led_on = false;
}

/********************************************** 
 * VIRTUAL FUNCTION 
 */
void RGBButton::update_leds() {  
}

void RGBButton::momentary_button (bool _is_momentary){
    is_momentary = _is_momentary;
}


