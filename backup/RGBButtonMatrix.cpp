#include "WProgram.h"
#include "RGBButtonMatrix.h"


RGBButtonMatrix::RGBButtonMatrix(int _ID, int _input_pin, int _states) : RGBButton(_ID, _input_pin, _states) {
    max_bright = LED_MAX_BRIGHT_MATRIX;
}

void RGBButtonMatrix::set_led_pins(int _LED_pin, int _R_pin, int _G_pin, int _B_pin) {
    led_on = true;
    led_available = true;
    
    led_button_pin = _LED_pin;
    led_pins[R] = _R_pin; 
    led_pins[G] = _G_pin;
    led_pins[B] = _B_pin;

    pinMode(led_button_pin, OUTPUT);
    pinMode(led_pins[R], OUTPUT);
    pinMode(led_pins[G], OUTPUT);
    pinMode(led_pins[B], OUTPUT);
}

void RGBButtonMatrix::update_leds() {  
    if(led_available) {
        if (led_on) {
            digitalWrite(led_pins[R], current_led_state[R]);
            digitalWrite(led_pins[G], current_led_state[G]);
            digitalWrite(led_pins[B], current_led_state[B]);
            digitalWrite(led_button_pin, LOW); 
            delayMicroseconds(30);
            digitalWrite(led_button_pin, HIGH); 
        } 
        else {
            digitalWrite(led_pins[R], LOW);
            digitalWrite(led_pins[G], LOW);
            digitalWrite(led_pins[B], LOW);
            digitalWrite(led_button_pin, HIGH); 
        }
    }
}



