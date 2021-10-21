#include "GetDigitalPinValue.hpp"

GetDigitalPinValue::GetDigitalPinValue(int pin) {
    this->_pin = pin;
}

int GetDigitalPinValue::getValue() {
    updateValue();
    return _value;
}

void GetDigitalPinValue::updateValue() {
    _value = digitalRead(_pin);
}

