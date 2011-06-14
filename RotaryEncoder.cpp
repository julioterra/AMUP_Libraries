#include "WProgram.h"
#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder(int _device_ID, int _component_ID, int _pinA, int _pinB) {
    pinA = _pinA;
    pinB = _pinB;
    pinMode(pinA, INPUT); 
    pinMode(pinB, INPUT); 
    ID = _component_ID;
    device_ID = _device_ID;

    digitalWrite(pinA, HIGH);       // turn on pullup resistor
    digitalWrite(pinB, HIGH);       // turn on pullup resistor

    encoderPos = 0;
    new_data = false;
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
    encoderPosPrevious = encoderPos;
    encoderPos = 0; 

    if (debug_code){
        Serial.print("RotaryEncoder::get_data() - encoder position: ");
        Serial.println(encoderPosPrevious, DEC);
    }

    return encoderPosPrevious;
}

int RotaryEncoder::get_print_state(){
    
    encoderPosPrevious = get_state();
    
    Serial.print(device_ID);
    Serial.print(" ");
    Serial.print(ID);
    Serial.print(" ");
    if (encoderPosPrevious == 65535) Serial.println("-1");
    else Serial.println(encoderPosPrevious);

    return encoderPosPrevious;
}



