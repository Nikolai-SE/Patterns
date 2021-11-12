#include "SetDigitalPinValue.hpp"

SetDigitalPinValue::SetDigitalPinValue(int pin){
    setPin(pin);
}
void SetDigitalPinValue::setPin(int pin) {
    _pin = pin;
    pinMode ( _pin, OUTPUT );
}
void SetDigitalPinValue::setValue(int value) {
    this->_value = value;
    digitalWrite(_pin, value);
}

